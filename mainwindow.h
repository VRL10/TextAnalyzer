#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPointer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class QNetworkAccessManager;
class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void setBusyUi(bool busy);
    void setStatusMessage(const QString &message, bool isError = false);
    void handleNetworkReply(QNetworkReply *reply);

    Ui::MainWindow *ui;
    QNetworkAccessManager *networkManager;
    QString selectedFilePath;
    QPointer<QNetworkReply> pendingReply;
};
#endif // MAINWINDOW_H
