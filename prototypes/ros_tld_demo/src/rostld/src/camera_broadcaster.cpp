#include "ros/ros.h"
#include "std_msgs/String.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <sstream>

std::string tempVideoFilePath = "/home/cts/hostworkspace/sep/rostld/test2.avi";

class CameraBroadcaster {
private:
    image_transport::ImageTransport imTransport;
    image_transport::Publisher imPub;

    CvCapture *camCapture;
    int frameCount;

public:
    CameraBroadcaster(ros::NodeHandle &nodeHandle, int cameraChoice)
        : imTransport(nodeHandle),
          frameCount(0)
    {
        imPub = imTransport.advertise(
            "/camera/frame", 1
        );

        camCapture = cvCaptureFromAVI(tempVideoFilePath.c_str());//cvCaptureFromCAM(-1);
        if(!camCapture) {
            //throw std::runtime_error("Could not initialise camera");
            throw std::runtime_error(tempVideoFilePath);
            return;
        }
    }

    ~CameraBroadcaster() {
        cvReleaseCapture(&camCapture);
    }

    void broadcastFrame(ros::Duration &out_frameDelta, bool &out_isComplete) {

        IplImage *rawFrame = cvQueryFrame(camCapture);
        if(!rawFrame) {
            //throw std::runtime_error("cvQueryFrame failed");
            out_isComplete = true;
            return;
        }
        out_isComplete = false;

        cv::Mat frame(rawFrame, false);
        cv_bridge::CvImagePtr framePtr;
        framePtr.reset(new cv_bridge::CvImage);
        framePtr.get()->encoding = "bgr8";
        frame.copyTo(framePtr->image);
        imPub.publish(framePtr->toImageMsg());

        frameCount++;
        out_frameDelta = ros::Duration(
                1.0/(double)cvGetCaptureProperty(camCapture, CV_CAP_PROP_FPS)
            *   (frameCount < 1700 ? 0.1 : 2)
        );
    }
};

int main(int argListLength, char **argList) {
    ros::init(argListLength, argList, "camera");
    ros::NodeHandle nodeHandle;

    // nodeHandle.param<std::string>("avipath", tempVideoFile, "WTF");

    // char *cwd = getcwd(0, 0);
    // std::cout << "cwd:" << cwd << std::endl;
    // ROS_INFO("MEOW: %s", cwd);
    // free(cwd);

    CameraBroadcaster camBroadcaster(nodeHandle, -1);
    while(ros::ok()) {
        ros::Duration frameDelta;
        bool isComplete;
        camBroadcaster.broadcastFrame(frameDelta, isComplete);
        if(isComplete) {
            break;
        }

        ros::spinOnce();

        frameDelta.sleep();
    }

    return 0;
}
