#ifndef PUTCHTEXT_H
#define PUTCHTEXT_H

/**


    \title
    opencv 显示中文

    \author
    bdus.00@gmail.com

    \date
    2018-4-1

    \details



    * OpenCV中输出汉字。字库提取采用了开源的FreeFype库。
    * QT环境中使用需要编码上的配置
    *
    * 显示汉字的时候需要一个汉字字库文件
    * 默认字体:
    *  "C:\\Windows\\Fonts\\simhei.ttf"
    *  请自行修改

    \include

    首先编译好 freetype库

    然后qt中配置：

     INCLUDEPATH += D:\opencv\opencv-3.2.0\build\include \
       D:\freetype-2.9\include

    CONFIG(debug,debug|release):{
        LIBS += D:\opencv\opencv-3.2.0\build\x64\vc14\lib\opencv_world320d.lib \
                D:\freetype-2.9\objs\x64\Debug\freetype.lib

    }else:{
        LIBS += D:\opencv\opencv-3.2.0\build\x64\vc14\lib\opencv_world320.lib \
                D:\freetype-2.9\objs\x64\Release\freetype.lib
    }


    \code


    ChText mych;
    //mych.Config(CH_FONT_SIMHEI,35,CV_RGB(255,0,0),0.5,0.3,0.5);
    //mych.putChText(img1,"你好agag哈哈哈哈哈哈",cv::Point2f(0,40),20,CV_RGB(255,0,0),CH_FONT_SIMHEI,0.5,0.3,0.5);
    mych.putChText(img1,"你好agag哈哈哈哈哈哈",cv::Point2f(0,40),35,CV_RGB(255,0,0));

    cv::namedWindow("ChText");
    cv::imshow("ChText",img1);

    \param
//    void putChText(
//            cv::Mat & frame_copy,                   要输入文字的图片
//            const char * msg_conStr,                要输入的文字
//            cv::Point point_ld,                     文字输入在图片的什么位置 ld意思是原点在BOTTOM_LEFT
//            double fontScale,                       字号
//            cv::Scalar color_cv,                    字体颜色
//            CH_FONT fontFace_Zh,                    字体 字体文件是要自己在源码里面改动的 如果是win环境 默认有黑体
//            double space_radio,                     空白符比例
//            double sep_radio,                       间隔比例
//            double transp_radio                     字体透明度
//            );


**/

#include <ft2build.h>
#include FT_FREETYPE_H
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

#include <wchar.h>
#include <assert.h>
#include <locale.h>
#include <ctype.h>

//#ifndef Qt_Encoding
#define Qt_Encoding
#ifdef Qt_Encoding
#include <QString>
#include <QTextCodec>
#include <QObject>
#endif
//#endif


#ifndef _Ch_FONT_
#define _Ch_FONT_
//const char * CH_FONT_LIST_ [] = {
//    "C:\\Windows\\Fonts\\simhei.ttf"
//};
extern const char * CH_FONT_LIST_ [];
typedef enum {
    CH_FONT_SIMHEI = 0
}CH_FONT;
#endif


class ChText
{

public:
    //ChText();
    ChText(CH_FONT fontFace_Zh = CH_FONT_SIMHEI, double frontScale = 35, cv::Scalar color_cv = CV_RGB(255,255,255), double space_radio = 0.5, double sep_radio = 0.1, double transp_radio = 0.5);
    void Config(CH_FONT fontFace_Zh, double fontScale, cv::Scalar color_cv, double space_radio, double sep_radio,  double transp_radio);

    virtual ~ChText();

    #ifdef Qt_Encoding
    char * QEncodingCvt(const char * msg_constr);
    char * QEncodingCvt(const std::string & msg_constr);
    #endif

    //void putChText(cv::Mat & frame_copy, const wchar_t * text, cv::Point point_ld,  double fontScale = 35, cv::Scalar color_cv = CV_RGB(255,0,0), CH_FONT fontFace_Zh = CH_FONT_SIMHEI, double space_radio = 0.5, double sep_radio = 0.1, double transp_radio = 0.5);
    //void putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld, double fontScale = 35, cv::Scalar color_cv = CV_RGB(255,255,255), CH_FONT fontFace_Zh = CH_FONT_SIMHEI, double space_radio = 0.5, double sep_radio = 0.1, double transp_radio = 0.5);
    void putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld, double fontScale, cv::Scalar color_cv, CH_FONT fontFace_Zh, double space_radio, double sep_radio, double transp_radio);
    void putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld, double fontScale, cv::Scalar color_cv);
    void putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld, double fontScale);
    void putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld);

private:
    void putWChar(cv::Mat &frame, wchar_t wc, cv::Point &pos);
    void putWChar(IplImage *img, wchar_t wc, cv::Point &pos, cv::Scalar color);

    bool IsChange(CH_FONT fontFace_Zh, double fontScale, cv::Scalar color_cv, double space_radio, double sep_radio, double transp_radio);



private:
    FT_Library  library_;
    FT_Error    error_;
    FT_Face     face_;

    CH_FONT     bk_font;
    double      bk_fontScale;
    cv::Scalar  bk_color_cv;
    double      bk_space_radio;
    double      bk_sep_radio;
    double      bk_transparent_radio;


};

#endif // PUTCHTEXT_H
    //void putChWord(Mat & frame_copy, const std::string & msg_conStr, cv::Point point_ld, int fontFace_Zh, double frontScale, cv::Scalar color_cv, int thinkness, double space_radio = 0.5, double sep_radio = 0.1 );
