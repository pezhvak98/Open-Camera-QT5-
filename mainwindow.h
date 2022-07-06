#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/opencv.hpp>
#include <QPainter>
using namespace cv;

#include <iostream>
#include <QPainter>
using namespace std;

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
    void on_pushButton_open_webcam_clicked();

    void on_pushButton_close_webcam_clicked();

    void update_window();


    void on_rectangleCheck_clicked();

    void on_squareCheck_clicked();

    void on_horizontalSlider_rangeChanged(int min, int max);

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    VideoCapture cap;
    Mat frame;

    QImage qt_image;

};

#endif // MAINWINDOW_H
