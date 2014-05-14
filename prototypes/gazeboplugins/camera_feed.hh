#include <gazebo/common/Plugin.hh>
#include <gazebo/sensors/CameraSensor.hh>
#include <gazebo/rendering/Camera.hh>
#include <gazebo/gazebo.hh>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace gazebo
{
  class CameraPlugin : public SensorPlugin
  {
    public: CameraPlugin();

    public: virtual void Load(sensors::SensorPtr _sensor, sdf::ElementPtr _sdf);

    public: virtual void OnNewFrame(const unsigned char *_image,
                              unsigned int _width, unsigned int _height,
                              unsigned int _depth, const std::string &_format);

    protected: unsigned int width, height, depth;
    protected: std::string format;
    protected: cv::VideoWriter outputVideo;
    
    protected: sensors::CameraSensorPtr parentSensor;
    protected: rendering::CameraPtr camera;

    private: event::ConnectionPtr newFrameConnection;

  };
}