#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

//display a image
String windowName1 = "picture_001";
String windowName2 = "picture_002";
String filePath = "/Users/sooglejay/opencv/projects/test/test_opencv/pics/";
String imageName1 = "dota.jpg";
String imageName2 = "dota_logo.jpg";



/**
 1
 显示图片
 **/
void simpleDisplayImage()
{
    //1 get the Mat data of  a Image
    Mat matImage1=imread(filePath+imageName1);
    
    //2 create a window to show the image
    namedWindow(windowName1);
    
    //3 show  the image to the named window
    imshow(windowName1, matImage1);
    
    //4 write a new image file to disk
    imwrite(filePath+"jiangwei_001.jpg", matImage1);
}


/**
 2
 两种图片叠加，获取图片的感兴趣的区域
 **/
void addWeightROI()
{
    //imageROI is the interest range of matImage1,it is also do exactly expect to the matImage1
    //定义一个Mat类型，用于存放，图像的ROI
    Mat matImage1=imread(filePath+imageName1);
    Mat matImage2= imread(filePath+imageName2);
    Mat imageROI;
    printf("%d",matImage1.cols);
    //方法一
    imageROI=matImage1(Rect(matImage1.cols-400,matImage1.rows-400,matImage2.cols,matImage2.rows));
    //方法二
    //imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));
    //将logo加到原图上
    //第一个数字是第一张mat的透明度，第二个数字是第二张mat的透明度
    addWeighted(imageROI,0.5,matImage2,0.5,1,imageROI);
    //显示结果
    namedWindow(windowName2);
    imshow(windowName2,matImage1);//the argument is matImage1
    
    
}

/**
 3
 加载掩模 感兴趣区域
 **/
bool copyROI()
{
    //【1】读入图像
    Mat srcImage1= imread(filePath+imageName1);
    Mat logoImage= imread(filePath+imageName2);
    if(!srcImage1.data ) { printf("你妹，读取srcImage1错误~！ \n"); return false; }
    if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }
    
    //【2】定义一个Mat类型并给其设定ROI区域
    Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));
    
    //【3】加载掩模（必须是灰度图）
    Mat mask= imread("dota_logo.jpg",0);
    
    //【4】将掩膜拷贝到ROI
    logoImage.copyTo(imageROI,mask);
    
    //【5】显示结果
    namedWindow("<1>利用ROI实现图像叠加示例窗口");
    imshow("<1>利用ROI实现图像叠加示例窗口",srcImage1);
    
    return true;
}

//图像的三个通道 的颜色分离和合并
bool MultiChannelBlending()
{
    //【0】定义相关变量
    Mat srcImage;
    Mat logoImage;
    vector<Mat>channels;
    Mat  imageBlueChannel;
    
    //=================【蓝色通道部分】=================
    //     描述：多通道混合-蓝色分量部分
    //============================================
    
    //【1】读入图片
    logoImage=imread(filePath+imageName2,0);
    srcImage=imread(filePath+imageName1);
    
    if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
    if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }
    
    //【2】把一个3通道图像转换成3个单通道图像
    split(srcImage,channels);//分离色彩通道
    
    //【3】将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
    imageBlueChannel=channels.at(0);
    //【4】将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
    addWeighted(imageBlueChannel(Rect(500,50,logoImage.cols,logoImage.rows)),1.0,
                logoImage,0.5,0,imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
    
    //【5】将三个单通道重新合并成一个三通道
    merge(channels,srcImage);
    
    //【6】显示效果图
    namedWindow(windowName1+1,WINDOW_AUTOSIZE);
    imshow(windowName1+1,srcImage);
    
    
    //=================【绿色通道部分】=================
    //     描述：多通道混合-绿色分量部分
    //============================================
    
    //【0】定义相关变量
    Mat  imageGreenChannel;
    
    //【1】重新读入图片
    logoImage=imread(filePath+imageName2,0);
    srcImage=imread(filePath+imageName1);
    
    if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
    if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }
    
    //【2】将一个三通道图像转换成三个单通道图像
    split(srcImage,channels);//分离色彩通道
    
    //【3】将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
    imageGreenChannel=channels.at(1);
    //【4】将原图的绿色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中
    addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
                logoImage,0.5,0.,imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
    
    //【5】将三个独立的单通道重新合并成一个三通道
    merge(channels,srcImage);
    
    //【6】显示效果图
    namedWindow(windowName1+2);
    imshow(windowName1+2,srcImage);
    
    
    
    //=================【红色通道部分】=================
    //     描述：多通道混合-红色分量部分
    //============================================
    
    //【0】定义相关变量
    Mat  imageRedChannel;
    
    //【1】重新读入图片
    logoImage=imread(filePath+imageName2,0);
    srcImage=imread(filePath+imageName1);
    
    if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
    if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }
    
    //【2】将一个三通道图像转换成三个单通道图像
    split(srcImage,channels);//分离色彩通道
    
    //【3】将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
    imageRedChannel=channels.at(2);
    //【4】将原图的红色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中
    addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
                logoImage,0.5,0.,imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
    
    //【5】将三个独立的单通道重新合并成一个三通道
    merge(channels,srcImage);
    
    //【6】显示效果图
    namedWindow(windowName1+3);
    imshow(windowName1+3,srcImage);

    return true;
}


/**
 图像腐蚀
 **/
void erode()
{
    Mat src = imread(filePath+imageName1);//源图像
    Mat kornel = getStructuringElement(MORPH_RECT, Size(15,15));//核矩阵，作为腐蚀的程度
    Mat dst ;//结果存储
    erode(src, dst, kornel);
    imshow(windowName1, dst);
}

//图像模糊
void blur()
{
    Mat src = imread(filePath+imageName1);
    Mat dst;
    imshow(windowName1,src);
    blur(src, dst, Size(1,1));
    imshow(windowName2, dst);
}

//边缘检测
void canny()
{
    Mat src = imread(filePath+imageName1);
    Mat dst,edgt,grayImage;
    dst.create(src.size(),src.type());
    
    cvtColor(src, grayImage, COLOR_BGR2GRAY);
    imshow(windowName2, grayImage);

    blur(grayImage, edgt, Size(5,5));
    Canny(edgt, edgt, 3, 9,3);
    
    imshow(windowName1, edgt);

    
}
//从摄像头读入视频帧
void videoCapture()
{
    //方法1
    VideoCapture capture;
    capture.open(0);
    
    //方法2
    //VideoCapture capture(0);
    
    Mat frame;
    while (true) {
        capture>>frame;
        imshow("video", frame);
        if(waitKey(33)==27)
        {
            break;
        }
    }
}

//从摄像头获取视频帧，做高斯模糊，canny边缘检测
void videoCaptureAndBlurAndCanny()
{
    VideoCapture capture;
    capture.open(0);
    Mat frame;
    Mat gray;
    Mat edget;
    while (1) {
        capture>>frame;
        
    
        cvtColor(frame, gray, COLOR_BGR2GRAY);
        
        //使用内核3 x 3(2X3+1＝7)来去噪
        blur(gray, edget, Size(7,7));
        //边缘检测
        Canny(edget, edget, 0,30,3);
        
        imshow("video", edget);
        if(waitKey(33)==27)break;
        
    }
}
int main( )
{
//    simpleDisplayImage();
//    addWeightROI();
//    copyROI();
    videoCaptureAndBlurAndCanny();
    char c = waitKey();
    while (c!=27) {
        c=waitKey();
    }
}





