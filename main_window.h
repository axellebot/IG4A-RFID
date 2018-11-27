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
    void on_btnVersion_clicked();
    void on_btnSubmit_clicked();

private:
    Ui::MainWindow *ui;
    ReaderManager readerManager;
    void closeEvent(QCloseEvent *bar);
};

#endif // WIDGET_H
