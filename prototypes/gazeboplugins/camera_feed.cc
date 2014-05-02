//test
#include "camera_feed.hh"
#include <gazebo/sensors/DepthCameraSensor.hh>
#include <sstream>

using namespace gazebo;
GZ_REGISTER_SENSOR_PLUGIN(CameraPlugin)

/////////////////////////////////////////////////
CameraPlugin::CameraPlugin() : SensorPlugin()
{
}

/////////////////////////////////////////////////
void CameraPlugin::Load(sensors::SensorPtr _sensor, sdf::ElementPtr /*_sdf*/)
{
  this->objPosY.open("/home/samholmes/SEP-CTs/prototypes/gazeboplugins/objPosY.txt");
  this->objPosZ.open("/home/samholmes/SEP-CTs/prototypes/gazeboplugins/objPosZ.txt");

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


float Extrapolate(float vals[])
{
  float sum = 0;
  float lastPos = vals[5];
  float temp = 0;
  for (int i = 0; i < 5; i++)
  {
    temp = vals[i+1] - vals[i];
    sum += temp;
  }
  sum+=temp;
  sum = sum/1.0;
  float nextPos = lastPos + sum;

  return nextPos;
}

float Interpolate(float nextPos, math::Pose pose, int y)
{
  std::cout << "Rotations XYZ : " << std::endl;
  std::cout << pose.rot.x << " " << pose.rot.y << " " << pose.rot.z << " " << std::endl;
  float angle = 0;
  if (y == 1)
  {
    float xDif = pose.pos.x - 20;
    float yDif = pose.pos.y - nextPos;
    float hypo = sqrt(pow(xDif, 2) + pow(yDif, 2));
  
    angle = asin(yDif/hypo);
  }
  else
  {
    //Z movement
  }
  return angle;
}


/////////////////////////////////////////////////
void CameraPlugin::OnNewFrame(const unsigned char * _image,
                              unsigned int _width,
                              unsigned int _height,
                              unsigned int _depth,
                              const std::string &_format)
{
  if (getline(this->objPosY, this->curVals))
  {
    this->yPosArray[this->counter] = atof(this->curVals.c_str());
  }
  if (getline(this->objPosZ, this->curVals))
  {
    this->zPosArray[this->counter] = atof(this->curVals.c_str());
  }
  counter++;
  if (counter >= 6)
  {
    counter = 0;
    //send to extrap & interp
    float newY = Extrapolate(this->yPosArray);
    float newZ = Extrapolate(this->zPosArray);

    float angleX = Interpolate(newY, this->camera->GetWorldPose(), 1);

    this->camera->RotatePitch(angleX);
    
    //Interpolate(newZ, this->camera->GetWorldPose(), 2);

  }

  cv::Mat blah(
    cv::Size(_width, _height),
    CV_8UC3, (unsigned char *)_image
  );
  //cv:cvtColor(image, continuousRBGA, CV_BGR2RGB, 3);

  outputVideo.write(blah);
}






