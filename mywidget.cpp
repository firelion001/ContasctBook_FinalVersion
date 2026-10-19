#include "mywidget.h"
#include "ui_mywidget.h"
#include <QTextStream>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
void Write(QString Filename,QString str){
    QFile outFile(Filename);

    if(!outFile.open(QFile::WriteOnly | QFile::Text)){
        qDebug()<<"output file failed";
        return;
    }

    QTextStream out(&outFile);
    out.setEncoding(QStringConverter::System);
    out<<str;
    outFile.flush();
    outFile.close();
}
QString Read(QString Filename){
    QFile inFile(Filename);

    if(!inFile.open(QFile::ReadOnly | QFile::Text)){
        qDebug()<<"could not open file for read";
        return "";
    }

    QTextStream in(&inFile);
    in.setEncoding(QStringConverter::System);


    QString text = in.readAll();
    inFile.close();
    return text;
}


MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);

    QStringList ColTotle;

    ui->tableWidget->setColumnCount(4);
    ColTotle<<QStringLiteral("學號")<<QStringLiteral("班級")<<QStringLiteral("姓名")<<QStringLiteral("電話");
    ui->tableWidget->setHorizontalHeaderLabels(ColTotle);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_pushButton_clicked()
{
    QTableWidgetItem *col1,*col2,*col3,*col4;

    col1 = new QTableWidgetItem(ui->lineEdit_1->text());
    col2 = new QTableWidgetItem(ui->lineEdit_2->text());
    col3 = new QTableWidgetItem(ui->lineEdit_3->text());
    col4 = new QTableWidgetItem(ui->lineEdit_4->text());

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());



    ui->tableWidget->setItem(row, 0, col1);
    ui->tableWidget->setItem(row, 1, col2);
    ui->tableWidget->setItem(row, 2, col3);
    ui->tableWidget->setItem(row, 3, col4);
}

void MyWidget::on_pushButton_2_clicked()
{
    QString fileName;
    QString saveStr;
    fileName = QFileDialog::getSaveFileName(this,"匯出通訊錄",".",
                                            "csv(*.csv);;text(*.txt)");
    for(int i=0; i<ui->tableWidget->rowCount();i++)
    {
        for(int j=0; j<ui->tableWidget->columnCount();j++)
        {
            saveStr += ui->tableWidget->item(i,j)->text()+",";
        }
        saveStr += "\n";
    }
    Write(fileName,saveStr);
}


void MyWidget::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"匯入通訊錄",".",
                                                    "csv(*.csv);;text(*.txt)");

    QString data = Read(fileName);
    QStringList rows = data.split("\n", Qt::SkipEmptyParts);

    ui->tableWidget->setRowCount(0);

    for(int i=0;i<rows.size();i++){
        QStringList cols = rows[i].split(",");

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        for(int j=0;j<ui->tableWidget->columnCount() && j<cols.size();j++){
            ui->tableWidget->setItem(row, j, new QTableWidgetItem(cols[j]));
        }
    }
}