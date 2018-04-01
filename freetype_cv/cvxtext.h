#ifndef CVXTEXT_H
#define CVXTEXT_H
#pragma once
//====================================================================
//====================================================================
//
// 文件: CvxText.h
//
// 说明: OpenCV汉字输出
//
// 时间: 2018-4-1
//
// 作者: chaishushan#gmail.com; bdus.00@gmail.com
//
//====================================================================
//====================================================================


/**
* \file CvxText.h
* \brief OpenCV汉字输出接口
*
* 实现了汉字输出功能。
*/

#include <ft2build.h>

//#include <freetype/freetype.h>


#include FT_FREETYPE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QTextCodec>
#include <QObject>
#include <QString>

/**
* \class CvxText
* \brief OpenCV中输出汉字
*
* OpenCV中输出汉字。字库提取采用了开源的FreeFype库。由于FreeFype是
* GPL版权发布的库，和OpenCV版权并不一致，因此目前还没有合并到OpenCV
* 扩展库中。
*
* 显示汉字的时候需要一个汉字字库文件，字库文件系统一般都自带了。
*
*
*
*\include
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



* \code
    CvxText CHword("C:\\Windows\\Fonts\\simhei.ttf");

    float p = 0.8;
    CvScalar myScale(35,0.5,0.3,0); //字体大小 20 空白字符大小比例 0.5  间隔大小比例 0.1 旋转角度(不支持) 0
    CHword.setFont(NULL,&myScale,NULL,&p);

    CHword.putText(img,"你好",cv::Point2f(0,40),CV_RGB(255,0,0));
    cv::namedWindow("CvxText");
    cv::imshow("CvxText",img);

}
* \endcode
*/

class CvxText
{
        // 禁止copy

        CvxText& operator=(const CvxText&);

        //================================================================
        //================================================================

public:

        /**
        * 装载字库文件
        */


        CvxText(const char *freeType);
        virtual ~CvxText();

        //================================================================
        //================================================================

        /**
        * 获取字体。目前有些参数尚不支持。
        *
        * \param font        字体类型, 目前不支持
        * \param size        字体大小/空白比例/间隔比例/旋转角度
        * \param underline   下画线
        * \param diaphaneity 透明度
        *
        * \sa setFont, restoreFont
        */

        void getFont(int *type,
                CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);

        /**
        * 设置字体。目前有些参数尚不支持。
        *
        * \param font        字体类型, 目前不支持
        * \param size        字体大小/空白比例/间隔比例/旋转角度
        * \param underline   下画线
        * \param diaphaneity 透明度
        *
        * \sa getFont, restoreFont
        */

        void setFont(int *type,
                CvScalar *size = NULL, bool *underline = NULL, float *diaphaneity = NULL);

        /**
        * 恢复原始的字体设置。
        *
        * \sa getFont, setFont
        */

        void restoreFont();

        //================================================================
        //================================================================

        /**
        * 输出汉字(颜色默认为黑色)。遇到不能输出的字符将停止。
        *
        * \param img  输出的影象
        * \param text 文本内容
        * \param pos  文本位置
        *
        * \return 返回成功输出的字符长度，失败返回-1。
        */

        int putText(IplImage *img, const char    *text, CvPoint pos);

        /**
        * 输出汉字(颜色默认为黑色)。遇到不能输出的字符将停止。
        *
        * \param img  输出的影象
        * \param text 文本内容
        * \param pos  文本位置
        *
        * \return 返回成功输出的字符长度，失败返回-1。
        */

        int putText(IplImage *img, const wchar_t *text, CvPoint pos);

        /**
        * 输出汉字。遇到不能输出的字符将停止。
        *
        * \param img   输出的影象
        * \param text  文本内容
        * \param pos   文本位置
        * \param color 文本颜色
        *
        * \return 返回成功输出的字符长度，失败返回-1。
        */
        int putText(cv::Mat &frame, const char *text, CvPoint pos, CvScalar color, double wordScale);
        int putText(cv::Mat &frame, const char    *text, CvPoint pos, CvScalar color);

        int putText(IplImage *img, const char    *text, CvPoint pos, CvScalar color);

        /**
        * 输出汉字。遇到不能输出的字符将停止。
        *
        * \param img   输出的影象
        * \param text  文本内容
        * \param pos   文本位置
        * \param color 文本颜色
        *
        * \return 返回成功输出的字符长度，失败返回-1。
        */
        int putText(cv::Mat &img, const wchar_t *text, CvPoint pos, CvScalar color);
        int putText(IplImage *img, const wchar_t *text, CvPoint pos, CvScalar color);

        //================================================================
        //================================================================

private:

        // 输出当前字符, 更新m_pos位置
        void putWChar(cv::Mat &frame, wchar_t wc, CvPoint &pos, CvScalar color);
        void putWChar(IplImage *img, wchar_t wc, CvPoint &pos, CvScalar color);

        //================================================================
        //================================================================

private:

        FT_Library   m_library;   // 字库
        FT_Face      m_face;      // 字体

                                                          //================================================================
                                                          //================================================================

                                                          // 默认的字体输出参数

        int         m_fontType;
        CvScalar   m_fontSize;
        bool      m_fontUnderline;
        float      m_fontDiaphaneity;

        //================================================================
        //================================================================
};

#endif // CVXTEXT_H
