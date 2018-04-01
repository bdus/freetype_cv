

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


#在Qt下使用
```cpp
#include "putchtext.h"
```

fooMain.h

	...
    ChText * CHTEXT;
	...
	void putChText(Mat & frame_copy, std::string & msg_conStr, cv::Point point_ld, int fontface_null, double fontsize, cv::Scalar color_cv, double thinkness_null);
    void putChText(Mat & frame_copy, const char msg_conStr[], cv::Point point_ld, int fontface_null, double fontsize, cv::Scalar color_cv, double thinkness_null, bool tran = false);
	...

	
fooMain.cpp

```cpp
void fooMain::putChText(Mat & frame_copy, const char msg_conStr[],cv::Point point_ld,int fontface_null,/*无效*/  double fontsize,cv::Scalar color_cv, double thinkness_null ,bool tran /*无效*/)
{
    CHTEXT->putChText(frame_copy,msg_conStr,point_ld,fontsize*12,color_cv /*  ... */);
}

void fooMain::putChText(Mat & frame_copy, std::string & msg_conStr,cv::Point point_ld,int fontface_null,/*无效*/  double fontsize,cv::Scalar color_cv, double thinkness_null /*无效*/)
{
    //
    //putText(frame_copy, event["event"].asString(), cv::Point2f(0, 40),cv::FONT_HERSHEY_PLAIN, 3, Scalar(0,0,255),3);

    //字典 中英文对照
    const std::string  msg_EnDict [] = {
        "Fall", "Running",  "Fight",    "Follow",   "Break", "Intrude"
    };
    const char * msg_ChDict [] = {
        "倒地",  "奔跑",  "打架",  "跟随",  "闯入", "禁入" //https://www.cnblogs.com/kuliuheng/archive/2013/10/30/3397796.html
    };
    //确定事件（英文）
    int i = 0;
    #define LENOF(X) ((int)sizeof(X)/(int)sizeof(X[0]))
    int len = LENOF(msg_EnDict);
    assert(LENOF(msg_ChDict) == len);
    for(;msg_conStr != msg_EnDict[i] && i < len; i++);

    //转换为中文

    CHTEXT->putChText(frame_copy,msg_ChDict[i],point_ld,fontsize*12,color_cv /*  ... */);
}
```




