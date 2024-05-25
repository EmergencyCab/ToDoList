#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QStandardPaths>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Creates a QFile object pointing to a text file in the user's document directory
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/toDoFile.txt");
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(this, "Error", file.errorString());
    } else {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QListWidgetItem* item = new QListWidgetItem(in.readLine(), ui->listWidget);
            ui->listWidget->addItem(item);
            item->setFlags(item->flags() | Qt::ItemIsEditable); // Make each item editable
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    writeListToFile(); // Call a function to write all tasks back to the file
    delete ui;  // Clean up the UI
}

void MainWindow::writeListToFile() {
    QFile file(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/toDoFile.txt");

    // Open the text file, clearing its contents (truncate)
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        QTextStream out(&file);
        for (int i = 0; i < ui->listWidget->count(); ++i) {
            out << ui->listWidget->item(i)->text() << "\n"; // Write each item's text followed by a newline to the file
        }
        file.close();
    } else {

        QMessageBox::information(this, "Error", file.errorString()); // If the file fails to open, display an error message
    }
}


void MainWindow::on_btnAdd_clicked()
{
    if (ui->txtTask->text().isEmpty()) return; // check if the input is empty

    QListWidgetItem* item = new QListWidgetItem(ui->txtTask->text(), ui->listWidget); // pass some text(ui->tstTask->text()) at item QlistWidget and the parent listWidget)
    ui->listWidget->addItem(item); // add item to listWidget so we pass the item
    item->setFlags(item->flags()| Qt::ItemIsEditable); // after adding the item we can edit it by double clicking
    ui->txtTask->clear(); // after typing the item name, it clears the text box for another input
    ui->txtTask->setFocus(); // after typing one item name, the cursor will be there on the box to type again
    writeListToFile();
}

void MainWindow::on_btnRemove_clicked() {
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    if (item) {
        delete item;
        writeListToFile();
    }
}

void MainWindow::on_btnRemoveAll_clicked() {
    ui->listWidget->clear();
    writeListToFile();
}
