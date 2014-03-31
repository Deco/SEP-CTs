#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>

#include <tld_utils.h>
#include <TLD.h>

std::string tempParamFilePath = "/home/cts/hostworkspace/sep/rostld/tldparams.yml";
int tempStartFrameDelay = 1860;//10;

class TLDTracker {
private:
    image_transport::ImageTransport imTransport;
    image_transport::Subscriber imSub;
    image_transport::Publisher imPub;

    TLD tld;
    bool isTrackingStarted;
    FILE *bbOutputFileHandle;
    cv::Mat prevFrameGray;
    BoundingBox pbox;
    std::vector<cv::Point2f> pts1;
    std::vector<cv::Point2f> pts2;
    bool status;
    int frameCount;

public:
    TLDTracker(ros::NodeHandle &nodeHandle)
        : imTransport(nodeHandle),
          tld(),
          bbOutputFileHandle(NULL),
          status(false),
          frameCount(0)
    {
        imSub = imTransport.subscribe(
            "/camera/frame", 10000,
            &TLDTracker::receiveFrameCallback, this
        );
        imPub = imTransport.advertise(
            "/tldtracker/processedFrame", 1
        );

        cv::FileStorage paramStorage;
        paramStorage.open(tempParamFilePath, cv::FileStorage::READ);
        tld.read(paramStorage.getFirstTopLevelNode());
        isTrackingStarted = false;

    }

    ~TLDTracker() {
        if(bbOutputFileHandle != NULL) {
            fclose(bbOutputFileHandle);
        }
    }

    void receiveFrameCallback(const sensor_msgs::ImageConstPtr& msg) {
        cv_bridge::CvImagePtr framePtr;
        try {
            framePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
        } catch(cv_bridge::Exception& e) {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }
        cv::Mat &frame = framePtr->image;
        cv::Size frameSize = frame.size();
        
        cv::Mat frameGray;
        cvtColor(frame, frameGray, CV_RGB2GRAY);
        cv::Rect initBox(
            //frameSize.width*0.48, frameSize.height*0.50,
            //frameSize.width*0.04, frameSize.height*0.40
            frameSize.width*0.20, frameSize.height*0.50,
            frameSize.width*0.40, frameSize.height*0.30
        );
        frameCount++;
        printf("frame #%d\n", frameCount);
        //char c; std::cin >> c;
        if(!isTrackingStarted && frameCount > tempStartFrameDelay) {
            isTrackingStarted = true;
            bbOutputFileHandle = fopen("/dev/null", "w");
            tld.init(frameGray, initBox, bbOutputFileHandle);
        }
        if(isTrackingStarted) {//} && frameCount%2 == 0) {
            pts1.clear(); pts2.clear();
            tld.processFrame(
                prevFrameGray, frameGray,
                pts1, pts2, pbox,
                status, true,
                bbOutputFileHandle
            );
        }
        //prevFrameGray = frameGray;
        cvtColor(frameGray, frame, CV_GRAY2RGB);
        if(status) {
            rectangle(frame,
                cvPoint(pbox.x, pbox.y),
                cvPoint(pbox.x+pbox.width, pbox.y+pbox.height),
                (tld.lastvalid ? cv::Scalar(0,255,0) : cv::Scalar(255,0,0)), 3
            );
            drawPoints(frame, pts1);
            drawPoints(frame, pts2, cv::Scalar(0,255,0));
        }
        //rectangle(frame, initBox, cvScalarAll(255), 3);

        //cv::circle(frame, cvPoint(50, 50), 10, CV_RGB(255, 0, 0), 4);
        imPub.publish(framePtr->toImageMsg());
        cv::swap(prevFrameGray, frameGray);
    }
};


int main(int argListLength, char **argList) {
    ros::init(argListLength, argList, "tldtracker");
    ros::NodeHandle nodeHandle;

    TLDTracker tldTracker(nodeHandle);
    
    ros::spin();

    return 0;
}

