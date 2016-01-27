//#include <opencv2/opencv.hpp>
//
//using namespace cv;
//using namespace std;
//
////display a image
//String windowName1 = "picture_001";
//String windowName2 = "picture_002";
//String filePath = "/Users/sooglejay/opencv/projects/test/test_opencv/pics/";
//String imageName1 = "dota.jpg";
//String imageName2 = "dota_logo.jpg";
//
//
//
///**
// 1
// 显示图片
// **/
//void simpleDisplayImage()
//{
//    //1 get the Mat data of  a Image
//    Mat matImage1=imread(filePath+imageName1,CV_LOAD_IMAGE_GRAYSCALE);
//    
//    //2 create a window to show the image
//    namedWindow(windowName1);
//    
//    //3 show  the image to the named window
//    imshow(windowName1, matImage1);
//    
//    //4 write a new image file to disk
//    imwrite(filePath+"jiangwei_001.jpg", matImage1);
//}
//
//
///**
// 2
// 两种图片叠加，获取图片的感兴趣的区域
// **/
//void addWeightROI()
//{
//    //imageROI is the interest range of matImage1,it is also do exactly expect to the matImage1
//    //定义一个Mat类型，用于存放，图像的ROI
//    Mat matImage1=imread(filePath+imageName1);
//    Mat matImage2= imread(filePath+imageName2);
//    Mat imageROI;
//    printf("%d",matImage1.cols);
//    //方法一
//    imageROI=matImage1(Rect(matImage1.cols-400,matImage1.rows-400,matImage2.cols,matImage2.rows));
//    //方法二
//    //imageROI=image(Range(350,350+logo.rows),Range(800,800+logo.cols));
//    //将logo加到原图上
//    //第一个数字是第一张mat的透明度，第二个数字是第二张mat的透明度
//    
//    // 公式 ：dst = src1[x]*alpha + src2[x]*beta +gamma; x是多维数组元素的索引值
//    addWeighted(imageROI,0.5,matImage2,0.5,1,imageROI);
//    //显示结果
//    namedWindow(windowName2);
//    imshow(windowName2,matImage1);//the argument is matImage1
//    
//    
//}
//
///**
// 3
// 加载掩模 感兴趣区域
// **/
//bool copyROIWithMask()
//{
//    //【1】读入图像
//    Mat srcImage1= imread(filePath+imageName1);
//    Mat logoImage= imread(filePath+imageName2);
//    if(!srcImage1.data ) { printf("你妹，读取srcImage1错误~！ \n"); return false; }
//    if(!logoImage.data ) { printf("你妹，读取logoImage错误~！ \n"); return false; }
//    
//    //【2】定义一个Mat类型并给其设定ROI区域
//    Mat imageROI= srcImage1(Rect(200,250,logoImage.cols,logoImage.rows));
//    Mat src2 = srcImage1.clone();
//    //【3】加载掩模（必须是灰度图）
//    Mat ma= imread(filePath+imageName2);
//    
//    //【4】将掩膜拷贝到ROI
//    logoImage.copyTo(imageROI,ma);
//    
//    //【5】显示结果
//    imshow(windowName1,srcImage1);
//    imshow(windowName2,src2);
//
//    
//    return true;
//}
//
////图像的三个通道 的颜色分离和合并
//bool MultiChannelBlending()
//{
//    //【0】定义相关变量
//    Mat srcImage;
//    Mat logoImage;
//    vector<Mat>channels;
//    Mat  imageBlueChannel;
//    
//    //=================【蓝色通道部分】=================
//    //     描述：多通道混合-蓝色分量部分
//    //============================================
//    
//    //【1】读入图片
//    logoImage=imread(filePath+imageName2,0);
//    srcImage=imread(filePath+imageName1);
//    
//    if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
//    if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }
//    
//    //【2】把一个3通道图像转换成3个单通道图像
//    split(srcImage,channels);//分离色彩通道
//    
//    //【3】将原图的蓝色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
//    imageBlueChannel=channels.at(0);
//    //【4】将原图的蓝色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageBlueChannel中
//    addWeighted(imageBlueChannel(Rect(500,50,logoImage.cols,logoImage.rows)),1.0,
//                logoImage,0.5,0,imageBlueChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
//    
//    //【5】将三个单通道重新合并成一个三通道
//    merge(channels,srcImage);
//    
//    //【6】显示效果图
//    namedWindow(windowName1+1,WINDOW_AUTOSIZE);
//    imshow(windowName1+1,srcImage);
//    
//    
//    //=================【绿色通道部分】=================
//    //     描述：多通道混合-绿色分量部分
//    //============================================
//    
//    //【0】定义相关变量
//    Mat  imageGreenChannel;
//    
//    //【1】重新读入图片
//    logoImage=imread(filePath+imageName2,0);
//    srcImage=imread(filePath+imageName1);
//    
//    if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
//    if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }
//    
//    //【2】将一个三通道图像转换成三个单通道图像
//    split(srcImage,channels);//分离色彩通道
//    
//    //【3】将原图的绿色通道的引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
//    imageGreenChannel=channels.at(1);
//    //【4】将原图的绿色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageGreenChannel中
//    addWeighted(imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
//                logoImage,0.5,0.,imageGreenChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
//    
//    //【5】将三个独立的单通道重新合并成一个三通道
//    merge(channels,srcImage);
//    
//    //【6】显示效果图
//    namedWindow(windowName1+2);
//    imshow(windowName1+2,srcImage);
//    
//    
//    
//    //=================【红色通道部分】=================
//    //     描述：多通道混合-红色分量部分
//    //============================================
//    
//    //【0】定义相关变量
//    Mat  imageRedChannel;
//    
//    //【1】重新读入图片
//    logoImage=imread(filePath+imageName2,0);
//    srcImage=imread(filePath+imageName1);
//    
//    if(!logoImage.data ) { printf("Oh，no，读取logoImage错误~！\n"); return false; }
//    if(!srcImage.data ) { printf("Oh，no，读取srcImage错误~！\n"); return false; }
//    
//    //【2】将一个三通道图像转换成三个单通道图像
//    split(srcImage,channels);//分离色彩通道
//    
//    //【3】将原图的红色通道引用返回给imageBlueChannel，注意是引用，相当于两者等价，修改其中一个另一个跟着变
//    imageRedChannel=channels.at(2);
//    //【4】将原图的红色通道的（500,250）坐标处右下方的一块区域和logo图进行加权操作，将得到的混合结果存到imageRedChannel中
//    addWeighted(imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)),1.0,
//                logoImage,0.5,0.,imageRedChannel(Rect(500,250,logoImage.cols,logoImage.rows)));
//    
//    //【5】将三个独立的单通道重新合并成一个三通道
//    merge(channels,srcImage);
//    
//    //【6】显示效果图
//    namedWindow(windowName1+3);
//    imshow(windowName1+3,srcImage);
//    
//    return true;
//}
//
//
///**
// 图像腐蚀
// **/
//void erode()
//{
//    Mat src = imread(filePath+imageName1);//源图像
//    Mat kornel = getStructuringElement(MORPH_RECT, Size(15,15));//核矩阵，作为腐蚀的程度
//    Mat dst ;//结果存储
//    erode(src, dst, kornel);
//    imshow(windowName1, dst);
//}
//
////图像模糊
//void blur()
//{
//    Mat src = imread(filePath+imageName1);
//    Mat dst;
//    imshow(windowName1,src);
//    blur(src, dst, Size(1,1));
//    imshow(windowName2, dst);
//}
//
////边缘检测
//void canny()
//{
//    Mat src = imread(filePath+imageName1);
//    Mat dst,edgt,grayImage;
//    dst.create(src.size(),src.type());
//    
//    cvtColor(src, grayImage, COLOR_BGR2GRAY);
//    imshow(windowName2, grayImage);
//    
//    blur(grayImage, edgt, Size(5,5));
//    Canny(edgt, edgt, 3, 9,3);
//    
//    imshow(windowName1, edgt);
//    
//    
//}
////从摄像头读入视频帧
//void videoCapture()
//{
//    //方法1
//    VideoCapture capture;
//    capture.open(0);
//    
//    //方法2
//    //VideoCapture capture(0);
//    
//    Mat frame;
//    while (true) {
//        capture>>frame;
//        imshow("video", frame);
//        if(waitKey(33)==27)
//        {
//            break;
//        }
//    }
//}
//
////从摄像头获取视频帧，做高斯模糊，canny边缘检测
//void videoCaptureAndBlurAndCanny()
//{
//    VideoCapture capture;
//    capture.open(0);
//    Mat frame;
//    Mat gray;
//    Mat edget;
//    while (1) {
//        capture>>frame;
//        
//        cvtColor(frame, gray, COLOR_BGR2GRAY);
//        
//        //使用内核3 x 3(2X3+1＝7)来去噪
//        blur(gray, edget, Size(7,7));
//        //边缘检测
//        Canny(edget, edget, 0,30,3);
//        
//        imshow("video", edget);
//        if(waitKey(33)==27)break;
//        
//    }
//}
//
////对比度和亮度调节公式：g(x)=a*f(x)+b ＝>  g(i,j)=a*f(i,j)+b
////a是调节对比度，b是偏置，调节亮度
//
////进度条的track bar 使用的全局变量
//int g_nContrastValue; //对比度值
//int g_nBrightValue;  //亮度值
//Mat g_srcImage,g_dstImage;
////回调函数
//void ContrastAndBright(int, void *)
//{
//    
//    
//    // 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
//    for( int y = 0; y < g_srcImage.rows; y++ )
//    {
//        for( int x = 0; x < g_srcImage.cols; x++ )
//        {
//            for( int c = 0; c < 3; c++ )
//            {
//                g_dstImage.at<Vec3b>(y,x)[c] =
//                saturate_cast<uchar>
//                (
//                   ( g_nContrastValue*0.01)*
//                   ( g_srcImage.at<Vec3b>(y,x)[c] ) +
//                     g_nBrightValue
//                );
//            }
//        }
//    }
//    printf("对比度:%d  ,亮度：%d \n",g_nContrastValue,g_nBrightValue);
//    
//    // 显示图像
//    imshow(windowName1, g_srcImage);//源图像都没有变
//    imshow(windowName2, g_dstImage);//变得都是目的图像
//}
////进度条 小程序
//void track()
//{
//    //改变控制台前景色和背景色
//    system("color 5F");
//    
//    // 读入用户提供的图像
//    g_srcImage = imread(filePath+imageName1);
//    if( !g_srcImage.data ) { printf("Oh，no，读取g_srcImage图片错误~！ \n"); return ; }
//    g_dstImage = Mat::zeros( g_srcImage.size(), g_srcImage.type() );
//    
//    //设定对比度和亮度的初值
//    g_nContrastValue=80;
//    g_nBrightValue=80;
//    
//    // 创建窗口
//    namedWindow(windowName1);//源图像窗口
//    namedWindow(windowName2);//目的图像窗口
//    
//    // 显示图像
//    imshow(windowName1, g_srcImage);//源图像都没有变
//    imshow(windowName2, g_dstImage);//变得都是目的图像
//    
//    //创建轨迹条
//    createTrackbar("对比度：", windowName1,&g_nContrastValue, 300,ContrastAndBright );
//    createTrackbar("亮   度：", windowName2,&g_nBrightValue, 200,ContrastAndBright );
//    
//    //调用回调函数
//    //    ContrastAndBright(g_nContrastValue,0);//回调函数可以写，也可以不写
//    //    ContrastAndBright(g_nBrightValue,0);//回调函数可以写，也可以不写
//    
//    cout<<"lalalala:"<< getTrackbarPos("对比度：", windowName1);
//    //输出一些帮助信息
//    cout<<endl<<"\t嗯。好了，请调整滚动条观察图像效果~\n\n"
//    <<"\t按下“esc”键时，程序退出~!\n";
//}
//
//
//
//
////鼠标程序，全局变量
//Rect g_rectangle;
//bool g_bDrawingBox = false;//是否进行绘制
//RNG g_rng(12345);
////画矩形函数，是鼠标小程序的辅助
//void DrawRectangle(cv::Mat& image,cv::Rect box)
//{
//    rectangle(image,
//              box.tl(),
//              box.br(),
//              //随机颜色
//              Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255 ),g_rng.uniform(0,255)));
//    
//}
////鼠标程序回调函数
//void on_MouseHandle(int event,int x,int y,int flags,void*param)
//{
//    Mat& image = *(cv::Mat*)param;
//    switch (event) {
//            
//            //鼠标移动消息
//        case EVENT_MOUSEMOVE:
//            if(g_bDrawingBox)
//            {
//                g_rectangle.width=x-g_rectangle.x;
//                g_rectangle.height=y-g_rectangle.y;
//            }
//            break;
//            //左键按下
//        case EVENT_LBUTTONDOWN:
//        {
//            g_bDrawingBox=true;
//            g_rectangle=Rect(x,y,0,0);//记录起始点
//        }
//            break;
//            //左键抬起
//        case EVENT_LBUTTONUP:
//            g_bDrawingBox=false;
//            if(g_rectangle.width<0)
//            {
//                g_rectangle.x+=g_rectangle.width;
//                g_rectangle.width*=-1;
//            }
//            if(g_rectangle.height<0)
//            {
//                g_rectangle.y+=g_rectangle.height;
//                g_rectangle.height*=-1;
//            }
//            DrawRectangle(image, g_rectangle);
//            break;
//            
//        default:
//            break;
//    }
//    
//}
//
////鼠标程序
//void testMouse()
//{
//    //1前期准备，设置参数
//    g_rectangle=Rect(-1,-1,0,0);
//    Mat srcImage(600,800,CV_8UC3),tempImage;
//    srcImage.copyTo(tempImage);
//    srcImage=Scalar::all(1);
//    
//    namedWindow(windowName1);
//    
//    //2设置回调参数
//    setMouseCallback(windowName1, on_MouseHandle,(void*)&srcImage);
//    
//    //3程序主循环
//    while (true) {
//        srcImage.copyTo(tempImage);//复制原图到临时变量
//        if(g_bDrawingBox)
//        {
//            DrawRectangle(tempImage,g_rectangle);
//        }
//        imshow(windowName1, tempImage);
//        if(waitKey(33)==27)break;
//    }
//    
//}
//
//
////减少颜色空间数
//void colorReduce(Mat & inputImage,Mat &outputImage ,int div)
//{
//    outputImage = inputImage.clone();
//    int rowNumber = outputImage.rows;
//    int colNumber = outputImage.cols;
//    
//    for(int i =0;i<rowNumber;i++)
//    {
//        //后面加或不加的区别是 图片的模糊程度
//        for (int j =0; j<colNumber; j++) {
//            outputImage.at<Vec3b>(i,j)[0]=outputImage.at<Vec3b>(i,j)[0]/div *div+div/2 ;
//            outputImage.at<Vec3b>(i,j)[1]=outputImage.at<Vec3b>(i,j)[1]/div *div+div/2 ;
//            outputImage.at<Vec3b>(i,j)[2]=outputImage.at<Vec3b>(i,j)[2]/div *div +div/2;
//
//        }
//        
////        //第二种方法
////        uchar* data = outputImage.ptr<uchar>(i);
////        for (int j=0; j<colNumber; j++) {
////            data[j]=data[j]/div * div + div/2;
////        }
//    }
//}
//
////图像膨胀操作
//void dilate()
//{
//    Mat A,B,C;
//    A = imread(filePath+imageName1);
//    imshow("A", A);
//    
//    Mat element = getStructuringElement(MORPH_RECT, Size(3,3));
//    dilate(A, B, element);
//    imshow("B", B);
//}
//
////图像腐蚀操作
//void erodeImage()
//{
//    
//    Mat A,B,C;
//    A = imread(filePath+imageName1);
//    imshow("A", A);
//    Mat element = getStructuringElement(MORPH_RECT, Size(3,3));
//    erode(A, B, element);
//    imshow("B", B);
//}
//
////尺寸变换
//void resize()
//{
//    Mat dst = Mat::zeros(512, 512, CV_8UC3);
//    Mat src = imread(filePath+imageName1);
////    resize(src, dst, dst.size(),INTER_LINEAR);
//    resize(src, dst,Size(src.rows/2,src.cols/2),0,0,3);
//
//    imshow(windowName1, src);
//    imshow(windowName2, dst);
//}
//
//
////图像金字塔和拉普拉斯变换
//void pyrUpAndDown()
//{
//    
//    Mat dst = Mat::zeros(100, 100, CV_8UC3);
//    Mat dstPyDown = Mat::zeros(100, 100, CV_8UC3);
//
//    Mat src = imread(filePath+imageName1);
//    pyrUp(src, dst);
//    pyrDown(src, dstPyDown);
//
//    imshow(windowName1, src);
//    imshow(windowName2+"pyrUp", dst);
//    imshow(windowName2+"pyrDown", dstPyDown);
//
//}
//
//
//
////图像的或值操作
//int g_nThresholdValue = 100;
//int g_nThresholdType = 3;
//Mat g_grayImage,g_grayImage2;
//Mat g_dstImage2;
////回调函数
//void on_Threshold(int ,void*)
//{
//    threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
//    imshow(windowName1, g_dstImage);
//}
////回调函数
//void on_Threshold2(int ,void*)
//{
//    threshold(g_grayImage2, g_dstImage2, g_nThresholdValue, 255, g_nThresholdType);
//    imshow(windowName2, g_dstImage2);
//}
////或值操作函数
//void threshold()
//{
//    g_srcImage = imread(filePath+imageName1);
//    cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
//    cvtColor(g_srcImage, g_grayImage2, COLOR_BGR2GRAY);
//
//    namedWindow(windowName1);
//    namedWindow(windowName2);
//
//    createTrackbar("模式", windowName1, &g_nThresholdType, 4,on_Threshold);
//    createTrackbar("参考值", windowName2, &g_nThresholdValue, 255,on_Threshold2);
//    on_Threshold(0,0);
//    on_Threshold2(0,0);
//
//}
//
//
////也是用于边缘检测
//void sobel()
//{
//    Mat grad_x,grad_y;
//    Mat abs_grad_x,abs_grad_y,dst;
//    
//    Mat src = imread(filePath+imageName1);
//    Sobel(src, grad_x, CV_16S, 1,0);
//    convertScaleAbs(grad_x, abs_grad_x);
//    imshow(windowName1, abs_grad_x);
//
//    
//    Sobel(src, grad_y, CV_16S, 0, 1);
//    convertScaleAbs(grad_y, abs_grad_y);
//    imshow(windowName2, abs_grad_y);
//    
//    addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
//    imshow("result", dst);
//}
//
////也用边缘检测，增强对比度
//void laplacian()
//{
//    Mat src,src_gray,dst,abs_dst;
//    src = imread(filePath+imageName1);
//    imshow(windowName1, src);
//    
//    //用高斯滤波消除噪声
//    GaussianBlur(src, src, Size(3,3), 0,0,BORDER_DEFAULT);
//    
//    cvtColor(src, src_gray, COLOR_BGR2GRAY);
//    
//    Laplacian(src_gray, dst, CV_16S,3,1,0,BORDER_DEFAULT);
//    
//    //计算结果，将结果转换成8位
//    convertScaleAbs(dst, abs_dst);
//    imshow(windowName2, abs_dst);
//    
//}
//
//int main()
//{
//    //    simpleDisplayImage();
//    //    addWeightROI();
//    //    copyROI();
//    laplacian();
//    char c = waitKey();
//    while (c!=27) {
//        c=waitKey();
//    }
//}
//
//
//
//
//
