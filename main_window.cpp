#include "main_window.h"
#include "ui_main_window.h"
#include "reader_manager.h"
#include <QtGui>
#include <QCloseEvent>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->readerManager = ReaderManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "APP_NAME",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        readerManager.disconnectReader();
        event->accept();
    }
}


void MainWindow::on_btnConnect_clicked()
{
    bool success = readerManager.connectReader();

    ui->lblDisplay->setText(success?"Succeed":"Failed");
    ui->lblDisplay->update();
}

void MainWindow::on_btnVersion_clicked(){
    int version = readerManager.getVersion();
    ui->lblDisplay->setText(QString(version));
    ui->lblDisplay->update();
}

void MainWindow::on_btnSubmit_clicked()
{
    QString Text = ui->txtSaisie->toPlainText();
    qDebug() << "Text : " << Text;
}
