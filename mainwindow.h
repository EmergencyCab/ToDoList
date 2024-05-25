#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAdd_clicked();
    void on_btnRemove_clicked();
    void on_btnRemoveAll_clicked();

private:
    Ui::MainWindow *ui;
    void writeListToFile(); // Correctly declare the function here
};

#endif // MAINWINDOW_H
