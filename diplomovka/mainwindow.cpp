#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compute.h"
#include <QFileDialog>
#include <QDir>
#include <vector>
#include <QMessageBox>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList QFiles;

void MainWindow::on_pushButton_clicked()
{
    QStringList newFiles = QFileDialog::getOpenFileNames(this, "Open a file", QDir::homePath());
    QFiles = QFiles + newFiles;
    ui->listWidget->addItems(newFiles);
}

void MainWindow::on_pushButton_2_clicked()
{
    std::vector<std::string> files;
    for (int i=0; i<QFiles.size(); i++) {
        std::string file = QFiles[i].toUtf8().constData();
        files.push_back(file);
    }
    bool permutation = ui->permutation->isChecked();
    bool allcycles = ui->allcycles->isChecked();
    bool cycleperm = ui->cycleperm->isChecked();
    bool halfperm = ui->halfperm->isChecked();
    bool cycledoublecover = ui->cycledoublecover->isChecked();
    bool clusters = ui->clusters->isChecked();

    if (files.size() > 0){
        if(!QDir().current().exists("results")){
            QDir().current().mkdir("results");
        }
        std::string currentDir = QDir().current().path().toUtf8().constData();
        std::vector<std::string>::iterator deleteDuplicates = std::unique(files.begin(),files.end());
        files.resize(std::distance(files.begin(), deleteDuplicates));
        computeFiles(files, permutation, allcycles, cycleperm, halfperm, cycledoublecover, clusters, currentDir);
        this->close();
    } else {
        QMessageBox::about(this,"Files error", "No files selected! Please select which files to test.");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QList<QListWidgetItem*> items = ui->listWidget->selectedItems();
    foreach(QListWidgetItem * item, items)
    {
        QFiles.removeAt(ui->listWidget->row(item));
        delete ui->listWidget->takeItem(ui->listWidget->row(item));
    }

//    if(!QDir().current().exists("results")){
//        QDir().current().mkdir("results");
//    }
    //QFiles.clear();
    //ui->listWidget->clear();
    //QMessageBox::about(this,"Files error", QDir().current().path());
}
