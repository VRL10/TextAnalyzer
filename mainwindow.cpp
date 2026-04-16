#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDateTime>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QHttpMultiPart>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QPushButton>
#include <QTimer>
#include <QUrl>


// Esse arquivo implementa o comportamento da janela (o "cérebro")

namespace {
constexpr int kRequestTimeoutMs = 30 * 1000;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    setWindowTitle("Cliente - Trabalho 04 (Sistemas Distribuidos)");
    ui->lineEditMasterUrl->setText("http://localhost:8080/processar");
    ui->lineEditArquivo->setReadOnly(true);
    ui->plainTextEditResultado->setReadOnly(true);

    // Quando usuário clica em "Selecionar", abre uma janela para escolher o .txt
    connect(ui->pushButtonSelecionar, &QPushButton::clicked, this, [this]() {
        const QString filePath = QFileDialog::getOpenFileName(
            this,
            "Selecionar arquivo .txt",
            QString(),
            "Arquivos de texto (*.txt);;Todos os arquivos (*.*)");

        if (filePath.isEmpty()) {
            return;
        }

        selectedFilePath = filePath;
        ui->lineEditArquivo->setText(filePath);
        setStatusMessage("Arquivo selecionado com sucesso.");
    });

    // Lê o arquivo e envia via HTTP para o servidor
    connect(ui->pushButtonEnviar, &QPushButton::clicked, this, [this]() {
        if (pendingReply) {
            QMessageBox::information(this,
                                     "Requisicao em andamento",
                                     "Aguarde a requisicao atual terminar.");
            return;
        }

        const QUrl url = QUrl::fromUserInput(ui->lineEditMasterUrl->text().trimmed());
        if (!url.isValid() || url.scheme().isEmpty() || url.host().isEmpty()) {
            setStatusMessage("URL do Mestre invalida.", true);
            return;
        }

        if (selectedFilePath.isEmpty()) {
            setStatusMessage("Selecione um arquivo .txt antes de enviar.", true);
            return;
        }

        QFile file(selectedFilePath);
        if (!file.exists()) {
            setStatusMessage("Arquivo selecionado nao existe mais.", true);
            return;
        }

        if (!file.open(QIODevice::ReadOnly)) {
            setStatusMessage("Nao foi possivel abrir o arquivo para leitura.", true);
            return;
        }

        const QByteArray fileData = file.readAll();
        if (fileData.isEmpty()) {
            setStatusMessage("Arquivo vazio. Selecione um .txt com palavras.", true);
            return;
        }

        const QFileInfo fileInfo(file);

        auto *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        QHttpPart filePart;
        filePart.setHeader(
            QNetworkRequest::ContentDispositionHeader,
            QString("form-data; name=\"arquivo\"; filename=\"%1\"").arg(fileInfo.fileName()));
        filePart.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain; charset=utf-8");
        filePart.setBody(fileData);
        multiPart->append(filePart);

        // Campo adicional para facilitar compatibilidade com implementacoes que recebem texto direto.
        QHttpPart textPart;
        textPart.setHeader(QNetworkRequest::ContentDispositionHeader, "form-data; name=\"texto\"");
        textPart.setBody(fileData);
        multiPart->append(textPart);

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::UserAgentHeader, "cliente-trabalho04-qt/1.0");
        request.setRawHeader("Accept", "application/json");

        pendingReply = networkManager->post(request, multiPart);
        multiPart->setParent(pendingReply);

        setBusyUi(true);
        setStatusMessage("Enviando arquivo para o Mestre...");

        auto *timeout = new QTimer(pendingReply);
        timeout->setSingleShot(true);
        connect(timeout, &QTimer::timeout, pendingReply, [this]() {
            if (pendingReply) {
                pendingReply->abort();
            }
        });
        timeout->start(kRequestTimeoutMs);

        connect(pendingReply, &QNetworkReply::finished, this, [this]() {
            if (!pendingReply) {
                return;
            }

            QNetworkReply *reply = pendingReply;
            pendingReply.clear();
            handleNetworkReply(reply);
            reply->deleteLater();
            setBusyUi(false);
        });
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBusyUi(bool busy)
{
    ui->pushButtonSelecionar->setEnabled(!busy);
    ui->pushButtonEnviar->setEnabled(!busy);
    ui->lineEditMasterUrl->setEnabled(!busy);
}

void MainWindow::setStatusMessage(const QString &message, bool isError)
{
    const QString when = QDateTime::currentDateTime().toString("dd/MM/yyyy HH:mm:ss");
    const QString prefix = isError ? "ERRO" : "INFO";
    const QString line = QString("[%1] %2: %3").arg(when, prefix, message);

    ui->labelStatus->setText(line);
    ui->labelStatus->setStyleSheet(isError ? "color: #b00020;" : "color: #0b6623;");
}

// Recebe a resposta do servidor e mostra na tela (interface) para o usuário.
void MainWindow::handleNetworkReply(QNetworkReply *reply)
{
    const QByteArray responseBody = reply->readAll();

    if (reply->error() != QNetworkReply::NoError) {
        setStatusMessage(QString("Falha na requisicao HTTP: %1").arg(reply->errorString()), true);
        const QString bodyText = QString::fromUtf8(responseBody);
        if (!bodyText.trimmed().isEmpty()) {
            ui->plainTextEditResultado->setPlainText(bodyText);
        }
        return;
    }

    QJsonParseError parseError;
    const QJsonDocument jsonDoc = QJsonDocument::fromJson(responseBody, &parseError);

    if (parseError.error == QJsonParseError::NoError) {
        ui->plainTextEditResultado->setPlainText(
            QString::fromUtf8(jsonDoc.toJson(QJsonDocument::Indented)));
        setStatusMessage("Resposta JSON recebida com sucesso.");
        return;
    }

    // Exibe resposta crua quando o servidor nao retornar JSON valido.
    ui->plainTextEditResultado->setPlainText(QString::fromUtf8(responseBody));
    setStatusMessage("Resposta recebida, mas nao esta em JSON valido.", true);
}
