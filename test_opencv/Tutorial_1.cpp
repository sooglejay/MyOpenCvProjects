#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
int main( )
{
  
    //display a image
    String windowName1 = "picture_001";
    String filePath = "/Users/sooglejay/opencv/projects/test/test_opencv/pics/";
    String imageName1="dota.jpg";
    
    //there are simple four steps 
    //1 get the Mat data of  a Image
    Mat matImage1=imread(filePath+imageName1);
    
    //2 create a window to show the image
    namedWindow(windowName1);
    
    //3 show  the image to the named window
    imshow(windowName1, matImage1);
    
    //4 write a new image file to disk
    imwrite(filePath+"jiangwei_001.jpg", matImage1);
    char c = waitKey();
    while (c!=27) {
        c=waitKey();
    }
    
    return 0;
}








