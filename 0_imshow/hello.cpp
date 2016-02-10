#include<opencv2/highgui/highgui.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

int main(){
    cv::Mat img;
    cv::Mat dst;
    cv::VideoCapture input(0);
    for(;;){
      if(!input.read(img)){
	break;
	}
       cv::Sobel(img, dst, CV_8U, 1,1);
       cv::imshow("camera", dst);
	char c = cv::waitKey(30);
	if (c==' '){
	break;
	}
    }
    return 0;
}
