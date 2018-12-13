#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include "reader_manager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();
    void on_btnDisconnect_clicked();
    void on_btnRead_clicked();
    void on_btnWrite_clicked();
    void on_btnPlus_clicked();
    void on_btnMinus_clicked();

    void on_txtSector_textChanged();

    void on_txtBlock_textChanged();

private:
    Ui::MainWindow *ui;
    ReaderManager *readerManager;
    void closeEvent(QCloseEvent *bar);
    void checkUIAvailability();
    void setFieldEnabled(bool enable);
    void setActionEnabled(bool enable);
    void setIncrementActionEnabled(bool enable);
};

#endif // WIDGET_H
