#include "mainwindow.h"
#include "ui_mainwindow.h"


#include FT_GLYPH_H


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //init Pic

    std::string path = "C:\\Users\\admin\\Documents\\qt\\qu_opencv\\aliens.jpg";
    cv::Mat img = cv::imread(path/*":/aliens.jpg"*/);
    assert(img.data);
    displayFrame(img);


}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::displayFrame(cv::Mat &frame)
{
    cv::cvtColor(frame,frame,CV_BGR2RGB);
    QImage qImg((const uchar *)frame.data,frame.cols,frame.rows,frame.cols*frame.channels(),QImage::Format_RGB888);

    QImage newImg = qImg.scaled(ui->label->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);

    this->ui->label->setPixmap(QPixmap::fromImage(newImg));

}

void MainWindow::SetText(std::string text)
{
    this->ui->label_2->setText(tr(text.c_str()));
}

void MainWindow::on_pushButton_2_clicked()
{

    cv::Mat img =  cv::imread("C:\\Users\\admin\\Documents\\qt\\qu_opencv\\aliens.jpg");//cv::Mat::zeros(face->glyph->bitmap.rows,face->glyph->bitmap.width,CV_8U);
    cv::namedWindow("img1");
    cv::imshow("img1",img);

    cv::Mat img1;
    img.copyTo(img1);



    ChText mych;
    //mych.Config(CH_FONT_SIMHEI,35,CV_RGB(255,0,0),0.5,0.3,0.5);
    //mych.putChText(img1,"你好agag哈哈哈哈哈哈",cv::Point2f(0,40),20,CV_RGB(255,0,0),CH_FONT_SIMHEI,0.5,0.3,0.5);
    mych.putChText(img1,"你好agag哈哈哈哈哈哈",cv::Point2f(0,40),35,CV_RGB(255,0,0));

    cv::namedWindow("ChText");
    cv::imshow("ChText",img1);


    CvxText CHword("C:\\Windows\\Fonts\\simhei.ttf");

    float p = 0.8;
    CvScalar myScale(35,0.5,0.3,0); //字体大小 20 空白字符大小比例 0.5  间隔大小比例 0.1 旋转角度(不支持) 0
    CHword.setFont(NULL,&myScale,NULL,&p);

    CHword.putText(img,"你好",cv::Point2f(0,40),CV_RGB(255,0,0),25);
    cv::namedWindow("CvxText");
    cv::imshow("CvxText",img);


}
