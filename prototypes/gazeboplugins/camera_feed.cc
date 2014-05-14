//test
#include "camera_feed.hh"
#include <gazebo/sensors/DepthCameraSensor.hh>

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(CameraPlugin)

/////////////////////////////////////////////////
CameraPlugin::CameraPlugin() : SensorPlugin()
{
}

/////////////////////////////////////////////////
void CameraPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  if (!_sensor)
    gzerr << "Invalid sensor pointer.\n";

  this->parentSensor =
    boost::shared_dynamic_cast<sensors::CameraSensor>(_sensor);

  if (!this->parentSensor)
  {
    gzerr << "CameraPlugin requires a CameraSensor.\n";
    if (boost::shared_dynamic_cast<sensors::DepthCameraSensor>(_sensor))
      gzmsg << "It is a depth camera sensor\n";
  }

  this->camera = this->parentSensor->GetCamera();

  if (!this->parentSensor)
  {
    gzerr << "CameraPlugin not attached to a camera sensor\n";
    return;
  }

  this->width = this->camera->GetImageWidth();
  this->height = this->camera->GetImageHeight();
  this->depth = this->camera->GetImageDepth();
  this->format = this->camera->GetImageFormat();

  this->newFrameConnection = this->camera->ConnectNewImageFrame(
      boost::bind(&CameraPlugin::OnNewFrame, this, _1, _2, _3, _4, _5));

  this->parentSensor->SetActive(true);

  outputVideo.open(
    "/home/samholmes/SEP-CTs/prototypes/gazeboplugins/output.avi", CV_FOURCC('M','J','P','G'),
    30, cv::Size(this->width, this->height), true
  );
}

/////////////////////////////////////////////////
void CameraPlugin::OnNewFrame(const unsigned char * _image,
                              unsigned int _width,
                              unsigned int _height,
                              unsigned int _depth,
                              const std::string &_format)
{
  cv::Mat blah(
    cv::Size(_width, _height),
    CV_8UC3, (unsigned char *)_image);
  //cv:cvtColor(image, continuousRBGA, CV_BGR2RGB, 3);

  outputVideo.write(blah);
}




