#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <ctime>
#include <string>
#include <sstream>
#include <signal.h>
#include <vector>
using namespace cv;
using namespace std;






#define CAP_WIDTH 1280  
#define CAP_HEIGHT 720
#define origin_w "Original window"
#define cor_w "cornerHarris Window"
#define new_w "New window"




static vector<Point> myPoint;
static Point p1,p2;
int win_count=0;

Mat frame;

void circle_update(){
  int count;
  for (vector<Point>::iterator it = myPoint.begin(); it!=myPoint.end();++it){
    circle(frame,*it,1,Scalar(255,255,255));
    cout<<"updated: "<<count<<endl;
    count++;
  }
  return;
}


static void cbMouse(int event,int x, int y, int flags, void* userdata);

static void cbMouse(int event,int x, int y, int flags, void* userdata){
  static bool p2_set=false;
  if(event==EVENT_LBUTTONDOWN && !p2_set){
    //start to draw a new window
    p1=Point(x,y);
    p2=Point(x,y);
    p2_set=false;
  }else if (event==EVENT_MOUSEMOVE && flags==EVENT_FLAG_LBUTTON){
    if(x>frame.size().width){
      x=frame.size().width;
    }
    else if(x<0){
      x=0;
    }
    if(y>frame.size().height){
      y=frame.size().height;
    }
    else if(y<0){
      y=0;
    }
    p2=Point(x,y);
    p2_set=true;
   
    
    //draw a rectangle here
  } 
  else if(event==EVENT_LBUTTONUP && p2_set){
    win_count++;
    Mat newSelect=frame(Rect(p1,p2));
    char window_name[20];
    sprintf(window_name,"This is selection: %d",win_count);
    imshow(window_name,newSelect);
    p1=Point(0,0);
    p2=Point(0,0);
    p2_set=false;
  }
  return ;
}



int main()
{
    char temp[50];
    double duration;
    int thred;
    float corThreshould[4]={0.0001,0.0001,0.0001,0.0001};
    
    Mat corImg;
    Mat surImg;
    Mat tmp_img;


    std::string valueText;
    std::clock_t start_clk;
    Scalar tempVal[4];
    VideoCapture cap(1);

    if(!cap.isOpened()){
      std::cout<<"This is not the correct cap"<<std::endl;
      return 0;
    }
    
    cap.set(CV_CAP_PROP_FRAME_WIDTH,CAP_WIDTH);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT,CAP_HEIGHT);
    namedWindow(origin_w,CV_WINDOW_AUTOSIZE);
    namedWindow(cor_w,CV_WINDOW_AUTOSIZE);
    setMouseCallback(origin_w,cbMouse,0);
    for(;;){
      
      
      createTrackbar("param","corImg_w",&thred,1000);
      cap >> frame;
      // cvtColor(frame,frame,CV_BGR2GRAY);
      // cornerHarris(frame,corImg,3,3,0.001);
      // threshold(corImg,corImg,0.0001,255,THRESH_BINARY);
      /*
      Mat block[4];
      // block[0]=Mat(blkCorImg,Rect(0,0,CAP_WIDTH/2,CAP_HEIGHT/2));
      // block[1]=Mat(blkCorImg,Rect(CAP_WIDTH/2-1,0,CAP_WIDTH/2,CAP_HEIGHT/2));
      // block[2]=Mat(blkCorImg,Rect(0,CAP_HEIGHT/2-1,CAP_WIDTH/2,CAP_HEIGHT/2));
      // block[3]=Mat(blkCorImg,Rect(CAP_WIDTH/2-1,CAP_HEIGHT/2,CAP_WIDTH/2,CAP_HEIGHT/2));
      
      // duration=( std::clock() - start_clk ) / (double) CLOCKS_PER_SEC;
      // std::cout<<"Frame T is: cor_w"<<duration<<std::endl;
      // start_clk=std::clock();
      
      // vector<KeyPoint> keypoints;
      
      //block[0]=frame();

      for (int i=0;i<4;i++){
        if(tempVal[i][0]<5){
          corThreshould[i]=corThreshould[i]*0.9;
          cout<<"new "<<i<<"is "<<corThreshould[i]<<endl;
        }
        else{
          corThreshould[i]*=1.1;
        }
        cornerHarris(block[i],block[i],3,3,0.0001);
        threshold(block[i],block[i],corThreshould[i],255,THRESH_BINARY);
        tempVal[i]=mean(block[i]);
        sprintf(temp,"%f.2",tempVal[i][0]);
        // valueText="Mean value is: "+std::string(temp)+"\n"+;
        stringstream ss;
        ss << "Mean value is: " << temp << endl;
        // cout << ss.str();
        putText(block[i], ss.str(), Point(10,10),FONT_HERSHEY_SIMPLEX,0.3, Scalar(255,255,255));
        // imshow("Block Image",block[i]);

      }


      */


      

      // SurfFeatureDetector surf(2500.);
      // surf.detect(frame,keypoints);

      // drawKeypoints(frame,keypoints,surImg,Scalar(255,0,0),
        // DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

      // circle_update();
      rectangle(frame,p1,p2,Scalar(255,255,255));
      imshow(origin_w,frame);
       // imshow("Block Image0",blkCorImg);
      // imshow("Canny Image",canImg);
      // imshow(cor_w,corImg);
      // imshow("SURF Image",surImg);
      if(waitKey(30)>=0){
        cap.release();
        break;}
  }
    return 0;
}