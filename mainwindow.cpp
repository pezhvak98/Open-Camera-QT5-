#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QLabel"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_open_webcam_clicked()
{
    cap.open(0);

    if(!cap.isOpened())
    {
        cout << "camera is not open" << endl;
    }
    else
    {
        cout << "camera is open" << endl;

        connect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
        timer->start(1);
    }
}

void MainWindow::on_pushButton_close_webcam_clicked()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(update_window()));
    cap.release();

    Mat image = Mat::zeros(frame.size(),CV_8UC3);

    qt_image = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());

    cout << "camera is closed" << endl;
}


void MainWindow::update_window()
{

    cap >> frame;
    frame.clone();

    if (ui->rectangleCheck->isChecked())
    {
        Point start_point(50,350);
        Point end_point(400,400);
        rectangle(frame, start_point, end_point, Scalar(0,0,255), 3, 8, 0);
    }

    if (ui->squareCheck->isChecked())
    {
        Point start_point(200,200);
        Point end_point(300,300);
        rectangle(frame, start_point, end_point, Scalar(230, 97, 0), 3, 8, 0);
    }


    cvtColor(frame, frame, COLOR_BGR2RGB);

    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);

    ui->label->setPixmap(QPixmap::fromImage(qt_image));

    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::on_rectangleCheck_clicked()
{

}


void MainWindow::on_squareCheck_clicked()
{

}

void MainWindow::on_horizontalSlider_rangeChanged(int min, int max)
{

}
