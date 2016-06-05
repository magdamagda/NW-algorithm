#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::on_btnCount_clicked()
{
    if(ui->checkBoxPararell->isChecked())
        calculatePararell();
    else
        calculateLinear();
}

void MainWindow::calculateLinear(){
    vector<char> signs;
    signs.push_back('A');
    signs.push_back('G');
    signs.push_back('C');
    signs.push_back('T');
    int values[4][4] = {
        {10, -1, -3, -4},
        {-1, 7, -5, -3},
        {-3, -5, 9, 0},
        {-4, -3, 0, 8}
    };
    int** matrix = new int*[4];
    for(int i=0; i<4; i++){
        matrix[i] = new int[4];
        for(int j=0; j<4; j++){
            matrix[i][j] = values[i][j];
        }
    }
    linearNeedlemanWunsch lnw(signs, matrix, ui->punishment->text().toInt());

    QTime startTime=QTime::currentTime();
    int result = lnw.calculate(ui->seq1->text().toStdString(), ui->seq2->text().toStdString());
    pair<string, string> path = lnw.getBackwardPath(ui->seq1->text().toStdString(), ui->seq2->text().toStdString());
    int mseconds = startTime.msecsTo(QTime::currentTime());

    ui->time->setText(QString::number(mseconds));
    ui->result->setText(QString::number(result));
    ui->best_fit1->setText(QString::fromStdString(path.first));
    ui->best_fit2->setText(QString::fromStdString(path.second));
}

void MainWindow::calculatePararell(){

}

void MainWindow::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Matrix file"), "/home/", tr("Text files (*.txt)"));
    ui->matriFile->setText(fileName);
}
