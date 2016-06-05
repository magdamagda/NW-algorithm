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
    pair<vector<char>, int **> matrix = readMatrix();
    linearNeedlemanWunsch lnw(matrix.first, matrix.second, ui->punishment->text().toInt());

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

pair<vector<char>, int **> MainWindow::readMatrix(){
    QString fileName = ui->matriFile->text();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           throw "Cannot open file";

    QTextStream in(&file);
    QString line = in.readLine();
    vector<char> signs;
    QStringList splitted = line.split("\t");
    int signsNum = splitted.size();
    for(int i=0; i<signsNum; i++){
        signs.push_back(splitted.at(i).at(0).toLatin1());
    }
    int** matrix = new int*[signsNum];
    int i=0;
    while (!in.atEnd()) {
        line = in.readLine();
        matrix[i] = new int[signsNum];
        splitted = line.split("\t");
        for(int j=0; j<signsNum; j++){
            matrix[i][j] = splitted.at(j).toInt();
        }
        i++;
    }
    return make_pair(signs, matrix);
}
