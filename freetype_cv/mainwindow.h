#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/opencv.hpp>

#include "cvxtext.h"
#include "putchtext.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void SetText(std::string text);

    ~MainWindow();



private slots:

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    void displayFrame(cv::Mat &frame);

};

#endif // MAINWINDOW_H
