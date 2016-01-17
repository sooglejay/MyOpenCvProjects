#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;

//display a image
String windowName1 = "picture_001";
String windowName2 = "picture_002";
String filePath = "/Users/sooglejay/opencv/projects/test/test_opencv/pics/";
String imageName1 = "dota.jpg";
String imageName2 = "dota_logo.jpg";



/**
 显示图片
 **/
void func1()
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
 两种图片叠加，获取图片的感兴趣的区域
 **/
void func2()
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
 
 **/
bool ROI_AddImage()
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


int main( )
{
    func1();
    func2();
    ROI_AddImage();
    char c = waitKey();
    while (c!=27) {
        c=waitKey();
    }
}





