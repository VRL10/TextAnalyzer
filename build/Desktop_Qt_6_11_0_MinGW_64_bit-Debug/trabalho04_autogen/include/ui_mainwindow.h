/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayoutPrincipal;
    QLabel *labelTitulo;
    QLabel *labelDescricao;
    QFormLayout *formLayoutConfig;
    QLabel *labelMasterUrl;
    QLineEdit *lineEditMasterUrl;
    QLabel *labelArquivo;
    QHBoxLayout *horizontalLayoutArquivo;
    QLineEdit *lineEditArquivo;
    QPushButton *pushButtonSelecionar;
    QHBoxLayout *horizontalLayoutAcoes;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonEnviar;
    QLabel *labelStatus;
    QLabel *labelResultado;
    QPlainTextEdit *plainTextEditResultado;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(900, 640);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayoutPrincipal = new QVBoxLayout(centralwidget);
        verticalLayoutPrincipal->setSpacing(10);
        verticalLayoutPrincipal->setObjectName("verticalLayoutPrincipal");
        verticalLayoutPrincipal->setContentsMargins(12, 12, 12, 12);
        labelTitulo = new QLabel(centralwidget);
        labelTitulo->setObjectName("labelTitulo");
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        labelTitulo->setFont(font);

        verticalLayoutPrincipal->addWidget(labelTitulo);

        labelDescricao = new QLabel(centralwidget);
        labelDescricao->setObjectName("labelDescricao");
        labelDescricao->setWordWrap(true);

        verticalLayoutPrincipal->addWidget(labelDescricao);

        formLayoutConfig = new QFormLayout();
        formLayoutConfig->setObjectName("formLayoutConfig");
        formLayoutConfig->setHorizontalSpacing(10);
        formLayoutConfig->setVerticalSpacing(8);
        labelMasterUrl = new QLabel(centralwidget);
        labelMasterUrl->setObjectName("labelMasterUrl");

        formLayoutConfig->setWidget(0, QFormLayout::ItemRole::LabelRole, labelMasterUrl);

        lineEditMasterUrl = new QLineEdit(centralwidget);
        lineEditMasterUrl->setObjectName("lineEditMasterUrl");

        formLayoutConfig->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEditMasterUrl);

        labelArquivo = new QLabel(centralwidget);
        labelArquivo->setObjectName("labelArquivo");

        formLayoutConfig->setWidget(1, QFormLayout::ItemRole::LabelRole, labelArquivo);

        horizontalLayoutArquivo = new QHBoxLayout();
        horizontalLayoutArquivo->setObjectName("horizontalLayoutArquivo");
        lineEditArquivo = new QLineEdit(centralwidget);
        lineEditArquivo->setObjectName("lineEditArquivo");

        horizontalLayoutArquivo->addWidget(lineEditArquivo);

        pushButtonSelecionar = new QPushButton(centralwidget);
        pushButtonSelecionar->setObjectName("pushButtonSelecionar");

        horizontalLayoutArquivo->addWidget(pushButtonSelecionar);


        formLayoutConfig->setLayout(1, QFormLayout::ItemRole::FieldRole, horizontalLayoutArquivo);


        verticalLayoutPrincipal->addLayout(formLayoutConfig);

        horizontalLayoutAcoes = new QHBoxLayout();
        horizontalLayoutAcoes->setObjectName("horizontalLayoutAcoes");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayoutAcoes->addItem(horizontalSpacer);

        pushButtonEnviar = new QPushButton(centralwidget);
        pushButtonEnviar->setObjectName("pushButtonEnviar");
        pushButtonEnviar->setMinimumSize(QSize(220, 34));

        horizontalLayoutAcoes->addWidget(pushButtonEnviar);


        verticalLayoutPrincipal->addLayout(horizontalLayoutAcoes);

        labelStatus = new QLabel(centralwidget);
        labelStatus->setObjectName("labelStatus");

        verticalLayoutPrincipal->addWidget(labelStatus);

        labelResultado = new QLabel(centralwidget);
        labelResultado->setObjectName("labelResultado");

        verticalLayoutPrincipal->addWidget(labelResultado);

        plainTextEditResultado = new QPlainTextEdit(centralwidget);
        plainTextEditResultado->setObjectName("plainTextEditResultado");

        verticalLayoutPrincipal->addWidget(plainTextEditResultado);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 900, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Cliente - Trabalho 04", nullptr));
        labelTitulo->setText(QCoreApplication::translate("MainWindow", "Cliente REST - Sistemas Distribuidos (Trabalho 04)", nullptr));
        labelDescricao->setText(QCoreApplication::translate("MainWindow", "Este cliente envia um arquivo .txt para o servidor Mestre via HTTP e exibe a resposta consolidada em JSON.", nullptr));
        labelMasterUrl->setText(QCoreApplication::translate("MainWindow", "URL do Mestre:", nullptr));
        lineEditMasterUrl->setPlaceholderText(QCoreApplication::translate("MainWindow", "Ex.: http://localhost:8080/processar", nullptr));
        labelArquivo->setText(QCoreApplication::translate("MainWindow", "Arquivo .txt:", nullptr));
        lineEditArquivo->setPlaceholderText(QCoreApplication::translate("MainWindow", "Nenhum arquivo selecionado", nullptr));
        pushButtonSelecionar->setText(QCoreApplication::translate("MainWindow", "Selecionar...", nullptr));
        pushButtonEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar arquivo ao Mestre", nullptr));
        labelStatus->setText(QCoreApplication::translate("MainWindow", "Status: aguardando acao do usuario.", nullptr));
        labelResultado->setText(QCoreApplication::translate("MainWindow", "Resposta do Mestre (JSON):", nullptr));
        plainTextEditResultado->setPlaceholderText(QCoreApplication::translate("MainWindow", "O resultado consolidado retornado pelo Mestre aparecera aqui.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
