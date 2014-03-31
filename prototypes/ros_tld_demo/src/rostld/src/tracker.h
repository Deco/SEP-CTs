
#include <opencv2/imgproc/imgproc.hpp>

struct BBox : public cv::Rect {
private:

public:
    float overlap;
    int sizeIndex;
    BBox() {
        //
    }
    BBox(const cv::Rect r)
        : cv::Rect(r)
    {
        //
    }
};

class Tracker {
private:

public:
    Tracker() {
        //
    }

    class Context;

    static void preprocessFrame(const cv::Mat &frame, cv::Mat &out_processedFrame) {
        out_processedFrame = frame;
    }



    void processFrame(
        const Context &currCtx, Context &out_newCtx
        const cv::Mat &prevFrame, const cv::Mat &currFrame
    ) {

    }

};

class Tracker::Context {
private:


public:
    Context() {
        // 
    }

};

