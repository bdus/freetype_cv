#include "putchtext.h"

#define TRY_(x) {error_ = x; if(error_) throw error_; }


const char * CH_FONT_LIST_ [] = {
    "C:\\Windows\\Fonts\\simhei.ttf"
};
//const std::string Ch_FONT_SIMHEI = "C:\\Windows\\Fonts\\simhei.ttf";


ChText::ChText(CH_FONT fontFace_Zh, double fontScale, cv::Scalar color_cv, double space_radio, double sep_radio, double transp_radio)
{
    error_ = FT_Init_FreeType(&library_);
    if(error_) throw error_;

    Config(fontFace_Zh,fontScale,color_cv,space_radio,sep_radio,transp_radio);
    setlocale(LC_ALL, "");
}

ChText::~ChText()
{

}

bool ChText::IsChange(CH_FONT fontFace_Zh, double fontScale, cv::Scalar color_cv, double space_radio, double sep_radio, double transp_radio)
{
    return (  (fontFace_Zh == bk_font) && \
              (fontScale == bk_fontScale) && \
              (color_cv == bk_color_cv) && \
              (space_radio == bk_space_radio) && \
              (sep_radio == bk_sep_radio) && \
              (transp_radio == bk_transparent_radio) \

            ) ? false : true;
}

void ChText::Config(CH_FONT fontFace_Zh, double fontScale, cv::Scalar color_cv, double space_radio, double sep_radio, double transp_radio)
{

    //INIT

    bk_color_cv = color_cv;
    bk_space_radio = space_radio;
    bk_sep_radio = sep_radio;
    bk_transparent_radio = transp_radio;

    //
//    if(fontFace_Zh != bk_font)
    {
        bk_font = fontFace_Zh;
        TRY_(FT_New_Face(library_,CH_FONT_LIST_[bk_font] ,0,&face_))
    }
//    if(fontScale != bk_fontScale)
    {
        bk_fontScale = fontScale;
        TRY_(FT_Set_Pixel_Sizes(face_,bk_fontScale,0))
    }
}


#undef TRY_

#ifdef Qt_Encoding
char * ChText::QEncodingCvt(const char * msg_constr)
{
    QString str = QObject::tr(msg_constr);
    QByteArray ba = str.toLocal8Bit();
    return ba.data();
}
char * ChText::QEncodingCvt(const std::string & msg_constr)
{
    return QEncodingCvt(msg_constr.c_str());
}
#endif

void ChText::putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld,  double fontScale, cv::Scalar color_cv)
{
    putChText(frame_copy,msg_conStr,point_ld,fontScale,color_cv,bk_font,bk_space_radio,bk_sep_radio,bk_transparent_radio);
}
void ChText::putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld,  double fontScale)
{
    putChText(frame_copy,msg_conStr,point_ld,fontScale,bk_color_cv,bk_font,bk_space_radio,bk_sep_radio,bk_transparent_radio);
}
void ChText::putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld)
{
    putChText(frame_copy,msg_conStr,point_ld,bk_fontScale,bk_color_cv,bk_font,bk_space_radio,bk_sep_radio,bk_transparent_radio);
}

void ChText::putChText(cv::Mat & frame_copy, const char * msg_conStr, cv::Point point_ld, double fontScale, cv::Scalar color_cv, CH_FONT fontFace_Zh, double space_radio, double sep_radio, double transp_radio)
{
    if(IsChange(fontFace_Zh,fontScale,color_cv,space_radio,sep_radio,transp_radio))
    {
        Config(fontFace_Zh,fontScale,color_cv,space_radio,sep_radio,transp_radio);
    }

    assert(!frame_copy.empty());
    assert(msg_conStr  != NULL);


    QString str = QObject::tr(msg_conStr);
    QByteArray ba = str.toLocal8Bit();
    char * text = ba.data();//QEncodingCvt(msg_conStr);//

    int i;
    for(i = 0; text[i] != '\0'; i++)
    {
        wchar_t wc = text[i];

        // 解析双字节符号
        if (!isascii(wc)) mbtowc(&wc, &text[i++], 2);

        putWChar(frame_copy,wc,point_ld);

    }

}

//void ChText::putChText(cv::Mat & frame_copy, const wchar_t * text, cv::Point point_ld,  double fontScale, cv::Scalar color_cv, CH_FONT fontFace_Zh ,double space_radio , double sep_radio, double transp_radio)
//{
//    if(IsChange(fontFace_Zh,fontScale,color_cv,space_radio,sep_radio,transp_radio))
//    {
//        Config(fontFace_Zh,fontScale,color_cv,space_radio,sep_radio,transp_radio);
//    }

//    assert(!frame_copy.empty());
//    assert(text  != NULL);


////    QString str = QObject::tr(msg_conStr);
////    QByteArray ba = str.toLocal8Bit();
////    char * text = ba.data();//QEncodingCvt(msg_conStr);//

//    int i;
//    for(i = 0; text[i] != '\0'; i++)
//    {
//        wchar_t wc = text[i];

//        putWChar(frame_copy,wc,point_ld);

//    }
//}

void ChText::putWChar(cv::Mat &frame, wchar_t wc, cv::Point &pos)
{

    //putWChar_(&IplImage(frame_copy),wc,point_ld,bk_color_cv);
    // 根据unicode生成字体的二值位图

        FT_UInt glyph_index = FT_Get_Char_Index(face_, wc);
        FT_Load_Glyph(face_, glyph_index, FT_LOAD_DEFAULT);
        FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_MONO);

        //

        FT_GlyphSlot slot = face_->glyph;

        // 行列数

        int rows = slot->bitmap.rows;
        int cols = slot->bitmap.width;

        int img_origin = 0; //  /*origin – Top-left IPL_ORIGIN_TL or bottom-left IPL_ORIGIN_BL  https://docs.opencv.org/2.4.9/modules/core/doc/old_basic_structures.html?highlight=origin#IplImage*%20cvInitImageHeader(IplImage*%20image,%20CvSize%20size,%20int%20depth,%20int%20channels,%20int%20origin,%20int%20align)*/


        double rate = bk_transparent_radio;

        for (int i = 0; i < rows; ++i)
        {
            //unsigned char * p  = frame.ptr<uchar>(i);
            for (int j = 0; j < cols; ++j)
            {
                int off = ((img_origin == 0) ? i : (rows - 1 - i))
                        * slot->bitmap.pitch + j / 8;

                if (slot->bitmap.buffer[off] & (0xC0 >> (j % 8)))
                {
                    int r = (img_origin == 0) ? pos.y - (rows - 1 - i) : pos.y + i;;
                    int c = pos.x + j ;

                    if (r >= 0 && r < frame.rows
                            && c >= 0 && c < frame.cols)
                    {
//                        p[j] = p[j] * ( 1- rate ) + color.val[0];
//                        p[j+1] = p[j+1] * ( 1- rate ) + color.val[1];
//                        p[j+2] = p[j+2] * ( 1- rate ) + color.val[2];
                        if(3 == frame.channels())
                        {
                            frame.at<cv::Vec3b>(r,c)[0] = frame.at<cv::Vec3b>(r,c)[0] * rate + bk_color_cv.val[0] * (1-rate);
                            frame.at<cv::Vec3b>(r,c)[1] = frame.at<cv::Vec3b>(r,c)[1] * rate + bk_color_cv.val[1] * (1-rate);
                            frame.at<cv::Vec3b>(r,c)[2] = frame.at<cv::Vec3b>(r,c)[2] * rate + bk_color_cv.val[2] * (1-rate);
                        }
                        else if (1 == frame.channels()) {
                            //frame.at<uchar>(r,c) = 0;

                        }
                    }
                }
            }
        }

        double space = bk_fontScale * bk_space_radio;
        double sep = bk_fontScale  * bk_sep_radio;

        pos.x += (int)((cols ? cols  : space) + sep);

}


void ChText::putWChar(IplImage *img, wchar_t wc, cv::Point &pos, cv::Scalar color)
{

        // 根据unicode生成字体的二值位图
    FT_UInt glyph_index = FT_Get_Char_Index(face_, wc);
    FT_Load_Glyph(face_, glyph_index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(face_->glyph, FT_RENDER_MODE_MONO);

    FT_GlyphSlot slot = face_->glyph;

    // 行列数

    int rows = slot->bitmap.rows;
    int cols = slot->bitmap.width;

        //
        for (int i = 0; i < rows; ++i)
        {
                for (int j = 0; j < cols; ++j)
                {
                        int off = ((img->origin == 0) ? i : (rows - 1 - i))
                                * slot->bitmap.pitch + j / 8;
                        /*origin – Top-left IPL_ORIGIN_TL or bottom-left IPL_ORIGIN_BL  https://docs.opencv.org/2.4.9/modules/core/doc/old_basic_structures.html?highlight=origin#IplImage*%20cvInitImageHeader(IplImage*%20image,%20CvSize%20size,%20int%20depth,%20int%20channels,%20int%20origin,%20int%20align)*/

                        if (slot->bitmap.buffer[off] & (0xC0 >> (j % 8)))
                        {
                                int r = (img->origin == 0) ? pos.y - (rows - 1 - i) : pos.y + i;;
                                int c = pos.x + j;

                                if (r >= 0 && r < img->height
                                        && c >= 0 && c < img->width)
                                {
                                        CvScalar scalar = cvGet2D(img, r, c);

                                        // 进行色彩融合

                                        float p = 0.5;
                                        for (int k = 0; k < 4; ++k)
                                        {
                                                scalar.val[k] = scalar.val[k] * (1 - p) + color.val[k] * p;
                                        }

                                        cvSet2D(img, r, c, scalar);
                                }
                        }
                } // end for
        } // end for

          // 修改下一个字的输出位置

        double space = bk_fontScale * bk_space_radio;
        double sep = bk_fontScale  * bk_sep_radio;

        pos.x += (int)((cols ? cols : space) + sep);
}
