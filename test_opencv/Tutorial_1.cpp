////
////  Tutorial_1.cpp
////  test_opencv
////
////  Created by sooglejay on 16/1/15.
////  Copyright © 2016年 sooglejay. All rights reserved.
////
//
//#include "Tutorial_1.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <math.h>
//#include <iostream>
//using namespace cv;
//using namespace std;
//static void help()
//{
//    cout
//    << "\nThis program illustrates the use of findContours and drawContours\n"
//    << "The original image is put up along with the image of drawn contours\n"
//    << "Usage:\n"
//    << "./contours2\n"
//    << "\nA trackbar is put up which controls the contour level from -3 to 3\n"
//    << endl;
//}
//const int w = 800;
//int levels = 3;
//vector<vector<Point> > contours;
//vector<Vec4i> hierarchy;
//static void on_trackbar(int, void*)
//{
//    Mat cnt_img = Mat::zeros(w, w, CV_8UC3);
//    int _levels = levels - 3;
//    drawContours( cnt_img, contours, _levels <= 0 ? 3 : -1, Scalar(128,255,255),
//                 3, LINE_AA, hierarchy, std::abs(_levels) );
//    imshow("contours", cnt_img);
//}
//int main( int argc, char** argv)
//{
//    cv::CommandLineParser parser(argc, argv, "{help h||}");
//    if (parser.has("help"))
//    {
//        help();
//        return 0;
//    }
//    Mat img = Mat::zeros(w, w, CV_8UC1);
//    //Draw 6 faces
//    for( int i = 0; i < 6; i++ )
//    {
//        int dx = (i%2)*250 - 30;
//        int dy = (i/2)*150;
//        const Scalar white = Scalar(255);
//        const Scalar black = Scalar(0);
//        if( i == 0 )
//        {
//            for( int j = 0; j <= 10; j++ )
//            {
//                double angle = (j+5)*CV_PI/21;
//                line(img, Point(cvRound(dx+100+j*10-80*cos(angle)),
//                                cvRound(dy+100-90*sin(angle))),
//                     Point(cvRound(dx+100+j*10-30*cos(angle)),
//                           cvRound(dy+100-30*sin(angle))), white, 1, 8, 0);
//            }
//        }
//        ellipse( img, Point(dx+150, dy+100), Size(100,70), 0, 0, 360, white, -1, 8, 0 );
//        ellipse( img, Point(dx+115, dy+70), Size(30,20), 0, 0, 360, black, -1, 8, 0 );
//        ellipse( img, Point(dx+185, dy+70), Size(30,20), 0, 0, 360, black, -1, 8, 0 );
//        ellipse( img, Point(dx+115, dy+70), Size(15,15), 0, 0, 360, white, -1, 8, 0 );
//        ellipse( img, Point(dx+185, dy+70), Size(15,15), 0, 0, 360, white, -1, 8, 0 );
//        ellipse( img, Point(dx+115, dy+70), Size(5,5), 0, 0, 360, black, -1, 8, 0 );
//        ellipse( img, Point(dx+185, dy+70), Size(5,5), 0, 0, 360, black, -1, 8, 0 );
//        ellipse( img, Point(dx+150, dy+100), Size(10,5), 0, 0, 360, black, -1, 8, 0 );
//        ellipse( img, Point(dx+150, dy+150), Size(40,10), 0, 0, 360, black, -1, 8, 0 );
//        ellipse( img, Point(dx+27, dy+100), Size(20,35), 0, 0, 360, white, -1, 8, 0 );
//        ellipse( img, Point(dx+273, dy+100), Size(20,35), 0, 0, 360, white, -1, 8, 0 );
//    }
//    //show the faces
//    namedWindow( "image", 1 );
//    imshow( "image", img );
//    //Extract the contours so that
//    vector<vector<Point> > contours0;
//    findContours( img, contours0, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE);
//    contours.resize(contours0.size());
//    for( size_t k = 0; k < contours0.size(); k++ )
//        approxPolyDP(Mat(contours0[k]), contours[k], 3, true);
//    namedWindow( "contours", 1 );
//    createTrackbar( "levels+3", "contours", &levels, 7, on_trackbar );
//    on_trackbar(0,0);
//    waitKey();
//    return 0;
//}













//-----------------------------------【程序说明】----------------------------------------------
//  程序名称:：【OpenCV入门教程之三】图像的载入，显示与输出 一站式剖析   配套源码
// VS2010版   OpenCV版本：2.4.8
//	 2014年3月5日 Create by 浅墨
//  描述： 图像的载入，显示与输出 一站式剖析   配套源码
//  图片素材出处：dota2原画 dota2logo  动漫人物
//	 配套博文链接：http://blog.csdn.net/poem_qianmo/article/details/20537737
//	 浅墨的微博：@浅墨_毛星云
//------------------------------------------------------------------------------------------------


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;


int main( )
{
    //-----------------------------------【一、图像的载入和显示】--------------------------------------
    //	描述：以下三行代码用于完成图像的载入和显示
    //--------------------------------------------------------------------------------------------------
    
    char name1[128] = "pictures1";
    char name2[128] = "pictures2";
    char name3[128] = "pictures3";

//    Mat girl=imread("girl.jpg"); //载入图像到Mat
//    namedWindow(name1); //创建一个名为 "【1】动漫图"的窗口
//    imshow(name1,girl);//显示名为 "【1】动漫图"的窗口
//    
    //-----------------------------------【二、初级图像混合】--------------------------------------
    //	描述：二、初级图像混合
    //-----------------------------------------------------------------------------------------------
    //载入图片
    Mat image= imread("dota.jpg",199);
    Mat logo= imread("dota_logo.jpg");
    
    //载入后先显示
    namedWindow(name2);
    imshow(name2,image);
    
    namedWindow(name3);
    imshow(name3,logo);
    
    // 定义一个Mat类型，用于存放，图像的ROI
    Mat imageROI;
    //方法一
    imageROI= image(Rect(800,350,logo.cols,logo.rows));
    //方法二
    //imageROI= image(Range(350,350+logo.rows),Range(800,800+logo.cols));
    
    // 将logo加到原图上
    addWeighted(imageROI,0.5,logo,0.3,0.,imageROI);
    
    //显示结果
    namedWindow("【4】原画+logo图");
    imshow("【4】原画+logo图",image);
    
    //-----------------------------------【三、图像的输出】--------------------------------------
    //	描述：将一个Mat图像输出到图像文件
    //-----------------------------------------------------------------------------------------------
    //输出一张jpg图片到工程目录下
    imwrite("我喜欢打dota2 by浅墨.jpg",image);
    
    waitKey();
    
    return 0;
}








