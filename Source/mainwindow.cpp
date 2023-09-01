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

}

QDataStream& operator>>(QDataStream& stream, HEADER_EXP_FILE& header)
{
    stream.device()->reset();
    stream.setByteOrder(QDataStream::LittleEndian);
    stream >> header.ExpPrescaler;
    stream >> header.FormatExportPoint.ValI32;
    stream >> header.TypeTest;
    return stream;
}

HEADER_EXP_FILE getHeader (QFile& ufile)
{
    HEADER_EXP_FILE FileHeader;
    ufile.open(QIODeviceBase::ReadOnly);
    QDataStream in(&ufile);    // read the data serialized from the file
    in >> FileHeader;

    return FileHeader;
}

void MainWindow::on_actionOpen_triggered()
{
    QFile sFile(QFileDialog::getOpenFileName(0, "Open", "", "*.bin"));
    HEADER_EXP_FILE FileHead;
    FileHead = getHeader(sFile);
    ui->txtOut->setText(QString::number(FileHead.ExpPrescaler));
    ui->txtIn->setText(QString::number(FileHead.TypeTest));
}

