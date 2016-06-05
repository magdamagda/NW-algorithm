#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <linearneedlemanwunsch.h>
#include <vector>
#include <utility>
#include <QTime>
#include <QFileDialog>
#include <QStringList>
#include <QTextStream>

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
    void on_btnCount_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void calculateLinear();
    void calculatePararell();
    pair<vector<char>, int**> readMatrix();
};

#endif // MAINWINDOW_H
