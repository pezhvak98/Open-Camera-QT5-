#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    cap.open(0);
    if(checked == 1)
    {
        closeWebcam();
        checked *= -1;
    }
    if(cap.isOpened())
    {
        openWebcam();
        checked *= -1;
    }
}

void MainWindow::updateWindow()
{
    cap >> frame;
    cvtColor(frame, frame, COLOR_BGR2RGB);
    on_rectangle_stateChanged();
    on_square_stateChanged();
    on_circle_stateChanged();
    qt_image = QImage((const unsigned char*) (frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_image));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::closeWebcam()
{
    disconnect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
    cap.release();
    Mat image = Mat::zeros(frame.size(),CV_8UC3);
    qt_image = QImage((const unsigned char*) (image.data), image.cols, image.rows, QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(qt_image));
    ui->label->resize(ui->label->pixmap()->size());
}

void MainWindow::openWebcam()
{
    connect(timer, SIGNAL(timeout()), this, SLOT(updateWindow()));
    timer->start(1);
}

void MainWindow::reset(int n)
{
    if(n == 1)
    {
        rect1.x = frame.cols / 2 - 30 ;
        rect1.y = frame.rows / 3 ;
        rect2.x = frame.cols / 2 + 30 ;
        rect2.y = frame.rows * 2 / 3 ;
    }

    if(n == 2)
    {
        sqr1.x = frame.cols / 2 - 40 ;
        sqr1.y = frame.rows / 2 - 40 ;
        sqr2.x = frame.cols / 2 + 40 ;
        sqr2.y = frame.rows / 2 + 40 ;
    }

    if(n == 3)
    {
        center.x = frame.cols / 2;
        center.y = frame.rows / 2;
        radius = 50 + (ratio + 1);
    }

}

void MainWindow::on_rectangle_stateChanged()
{

    if(ui->rectangle->isChecked())
    {
        if(startRect == true)
        {
            reset(1);
        }
        rectangle(frame, rect1, rect2, Scalar(200,0,0), 2);
    }
}

void MainWindow::on_square_stateChanged()
{

    if(ui->square->isChecked())
    {
        if(startSqr == true)
        {
            reset(2);
        }
        rectangle(frame, sqr1, sqr2, Scalar(0,0,200), 2);
    }
}

void MainWindow::on_circle_stateChanged()
{

    if(ui->circle->isChecked())
    {
        if(startCircle == true)
        {
            reset(3);
        }
        circle(frame, center, radius, Scalar(50,200,70), 2);
    }
}

void MainWindow::on_up_clicked()
{
    if(rect1.y > 0 && rect2.y > 0){
    if(ui->rectangle->isChecked())
    {
        rect1.y -= 15;
        rect2.y -= 15;
        startRect = false;
    }
    }
    if(sqr1.y > 0 && sqr2.y > 0){
    if(ui->square->isChecked())
    {
        sqr1.y -= 15;
        sqr2.y -= 15;
        startSqr = false;
    }
    }
    if(center.y > 50){
    if(ui->circle->isChecked())
    {
        center.y -= 10;
        startCircle = false;
    }
    }

}

void MainWindow::on_left_clicked()
 {
    if(rect1.x > 0 && rect2.x > 0){
    if(ui->rectangle->isChecked())
    {
        rect1.x -= 10;
        rect2.x -= 10;
        startRect = false;
    }
    }
    if(sqr1.x > 0 && sqr2.x > 0){
    if(ui->square->isChecked())
    {
        sqr1.x -= 10;
        sqr2.x -= 10;
        startSqr = false;
    }
    }
    if(center.x > 50){
    if(ui->circle->isChecked())
    {
        center.x -= 10;
        startCircle = false;
    }
    }
}

void MainWindow::on_right_clicked()
{
    if(rect1.x < frame.cols && rect2.x < frame.cols){
    if(ui->rectangle->isChecked())
    {
        rect1.x += 10;
        rect2.x += 10;
        startRect = false;
    }
    }
    if(sqr1.x < frame.cols && sqr2.x < frame.cols){
    if(ui->square->isChecked())
    {
        sqr1.x += 10;
        sqr2.x += 10;
        startSqr = false;
    }
    }
    if(center.x + 50 < frame.cols){
    if(ui->circle->isChecked())
    {
        center.x += 10;
        startCircle = false;
    }
    }
}

void MainWindow::on_down_clicked()
{
    if(rect1.y < frame.rows && rect2.y < frame.rows){
    if(ui->rectangle->isChecked())
    {
        rect1.y += 10;
        rect2.y += 10;
        startRect = false;
    }
    }
    if(sqr1.y < frame.rows && sqr2.y < frame.rows){
    if(ui->square->isChecked())
    {
        sqr1.y += 10;
        sqr2.y += 10;
        startSqr = false;
    }
    }
    if(center.y + 50 < frame.rows){
    if(ui->circle->isChecked())
    {
        center.y += 10;
        startCircle = false;
    }
    }

}
void MainWindow::on_pushButton_2_clicked()
{
    if(ui->rectangle->isChecked())
    {
        reset(1);
    }

    if(ui->square->isChecked())
    {
        reset(2);
    }

    if(ui->circle->isChecked())
    {
        reset(3);
    }

}

