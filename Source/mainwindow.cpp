#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "structures.h"
#include <QFileDialog>
#include <QDataStream>
#include <QFile>
using namespace std;




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnOK_clicked()
{
    ui->txtOut->setText(QString::number(ui->txtIn->text().toInt()*2));
}

HEADER_EXP_FILE getHeader (const QString ufile)
{
    HEADER_EXP_FILE FileHeader;

    return FileHeader;
}

void MainWindow::on_actionOpen_triggered()
{
    QString sFile(QFileDialog::getOpenFileName(0, "Open", "", "*.bin"));
    HEADER_EXP_FILE FileHead;
    FileHead = getHeader(sFile);
}

