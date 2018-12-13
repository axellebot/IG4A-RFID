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

/**
 * @brief MainWindow::closeEvent
 * @param event
 * Handling Close Window Event
 */
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

/**
 * @brief MainWindow::on_btnConnect_clicked
 * Handling Connect Button Clicked
 */
void MainWindow::on_btnConnect_clicked()
{
    int failed = readerManager->connectReader();
    if(failed==0){
        ui->txtVersion->setText(QString(readerManager->getVersion()));
        ui->txtVersion->update();
        ui->txtIdentity->setText(QString(readerManager->getId()));
        ui->txtIdentity->update();
    }
    this->checkUIAvailability();
}

/**
 * @brief MainWindow::on_btnDisconnect_clicked
 * Handing Disconnect Button Clicked
 */
void MainWindow::on_btnDisconnect_clicked()
{
    int failed = readerManager->disconnectReader();
    if(failed==0){
        ui->txtVersion->setText(QString(""));
        ui->txtVersion->update();
        ui->txtIdentity->setText(QString(""));
        ui->txtIdentity->update();
    }
    this->checkUIAvailability();
}

/**
 * @brief MainWindow::on_btnRead_clicked
 * Handling Read Button Clicked
 */
void MainWindow::on_btnRead_clicked(){
    QString text;

    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    this->readerManager->read(sector,block);

    this->ui->txtReadData->setPlainText(QString(this->readerManager->getData()));
}

/**
 * @brief MainWindow::on_btnWrite_clicked
 * Handling Write Button Clicked
 */
void MainWindow::on_btnWrite_clicked()
{
    QString text = ui->txtWriteData->toPlainText();
    QByteArray ba = text.toLocal8Bit();
    char * tmp = ba.data();

    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    readerManager->write(sector,block,tmp);
}

/**
 * @brief MainWindow::on_btnPlus_clicked
 * Handling Plus Button Clicked
 */
void MainWindow::on_btnPlus_clicked(){
    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    if(sector == 3 && block == 14 ){
        readerManager->increment(block);
    }
}

/**
 * @brief MainWindow::on_btnMinus_clicked
 * Handling Minus Button Clicked
 */
void MainWindow::on_btnMinus_clicked(){
    int sector = ui->txtSector->toPlainText().toInt();
    int block = ui->txtBlock->toPlainText().toInt();
    if(sector == 3 && block == 14 ){
        readerManager->decrement(block);
    }
}
/**
 * @brief MainWindow::on_txtSector_textChanged
 * Handling Sector Field Changed
 */
void MainWindow::on_txtSector_textChanged()
{
    this->checkUIAvailability();
}

/**
 * @brief MainWindow::on_txtBlock_textChanged
 * Handling Block Field Changed
 */
void MainWindow::on_txtBlock_textChanged()
{
    this->checkUIAvailability();
}

void MainWindow::checkUIAvailability(){
    if(readerManager->isConnected()){
        this->ui->btnConnect->setEnabled(false);
        this->ui->btnDisconnect->setEnabled(true);

        this->setFieldEnabled(true);
        if(ui->txtSector->toPlainText()!="" ) {
            this->setIncrementActionEnabled(true);
            if(ui->txtBlock->toPlainText()!=""){
                this->setActionEnabled(true);
            }else{
                this->setActionEnabled(false);
            }
        }else{
            this->setIncrementActionEnabled(false);
            this->setActionEnabled(false);
        }
    }else{
        this->ui->btnConnect->setEnabled(true);
        this->ui->btnDisconnect->setEnabled(false);
        this->setFieldEnabled(false);
        this->setIncrementActionEnabled(false);
        this->setActionEnabled(false);
    }
}

void MainWindow::setFieldEnabled(bool enable){
    this->ui->txtSector->setEnabled(enable);
    this->ui->txtBlock->setEnabled(enable);
    this->ui->txtWriteData->setEnabled(enable);
}

void MainWindow::setIncrementActionEnabled(bool enable){
    ui->btnPlus->setEnabled(enable);
    ui->btnMinus->setEnabled(enable);
}

void MainWindow::setActionEnabled(bool enable){
    ui->btnRead->setEnabled(enable);
    ui->btnWrite->setEnabled(enable);
}
