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
    this->readerManager = new ReaderManager();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete readerManager;
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
        event->accept();
    }
}

void MainWindow::on_btnConnect_clicked()
{
    int failed = readerManager->connectReader();
    if(failed==0){
        ui->btnConnect->setEnabled(false);
        ui->btnConnect->update();
        ui->btnDisconnect->setEnabled(true);
        ui->btnDisconnect->update();
        ui->txtVersion->setText(QString(readerManager->getVersion()));
        ui->txtVersion->update();
        ui->txtIdentity->setText(QString(readerManager->getId()));
        ui->txtIdentity->update();
    }
}

void MainWindow::on_btnDisconnect_clicked()
{
    int failed = readerManager->disconnectReader();
    if(failed==0){
        ui->btnDisconnect->setEnabled(false);
        ui->btnDisconnect->update();
        ui->btnConnect->setEnabled(true);
        ui->btnConnect->update();
        ui->txtVersion->setText(QString(""));
        ui->txtVersion->update();
        ui->txtIdentity->setText(QString(""));
        ui->txtIdentity->update();
    }
}

void MainWindow::on_btnWrite_clicked()
{
    uint8_t data[16];
    QString text = ui->txtWriteData->toPlainText();
    for(int k = 0; k <16; k++){
        data[k] = QChar(text[k]).unicode();
    }

    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    this->readerManager->write(sector,block,data);
}

void MainWindow::on_btnPlus_clicked(){
    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    if (block == 14 && sector == 3){
        readerManager->increment(block);
    }

}
void MainWindow::on_btnMinus_clicked(){
    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    if (block == 14 && sector == 3){
        readerManager->decrement(block);
    }
}
