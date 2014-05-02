#include <gazebo/common/Plugin.hh>
#include <gazebo/sensors/CameraSensor.hh>
#include <gazebo/rendering/Camera.hh>
#include <gazebo/gazebo.hh>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

namespace gazebo
{
  class CameraPlugin : public SensorPlugin
  {
    public: CameraPlugin();

    public: virtual void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf);

    public: virtual void OnNewFrame(const unsigned char *_image,
                              unsigned int _width, unsigned int _height,
                              unsigned int _depth, const std::string &_format);

    protected: unsigned int width, height, depth, counter;
    protected: std::string format;
    protected: cv::VideoWriter outputVideo;
    
    private: physics::ModelPtr model;

    protected: sensors::CameraSensorPtr parentSensor;
    protected: rendering::CameraPtr camera;
    private: std::ifstream objPosY;
    private: std::ifstream objPosZ;
    private: float zPosArray[7];
    private: float yPosArray[7];
    private: std::string curVals;

    private: event::ConnectionPtr newFrameConnection;

  };
}