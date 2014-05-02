#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>
#include <iostream>
#include <fstream>

namespace gazebo
{
  class ObjectPos : public WorldPlugin
  {
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
    {
            
      // Store the pointer to the world
      this->world = _world;
      //this->objPosY.open("/home/samholmes/SEP-CTs/prototypes/gazeboplugins/objPosY.txt");
      //this->objPosZ.open("/home/samholmes/SEP-CTs/prototypes/gazeboplugins/objPosZ.txt");

      this->model = this->world->GetModel("box");
      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&ObjectPos::OnUpdate, this, _1));
    }

    // Called by the world update start event
    public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
      //math::Pose pose = this->model->GetWorldPose();
      //objPosY << pose.pos.y << std::endl;
      //objPosZ << pose.pos.z << std::endl;
    }

    private: physics::ModelPtr model;

    private: std::ofstream objPosZ;
    private: std::ofstream objPosY;

    // Pointer to the model
    private: physics::WorldPtr world;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_WORLD_PLUGIN(ObjectPos)
}