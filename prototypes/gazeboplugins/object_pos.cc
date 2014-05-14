#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

namespace gazebo
{
  class ObjectPos : public WorldPlugin
  {
    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
    {
            
      // Store the pointer to the world
      this->world = _world;
      
      transport::NodePtr node(new transport::Node());
      node->Init(_world->GetName());
      this->posePub = node->Advertise<msgs::Pose>("~/test");

      this->model = this->world->GetModel("box");
      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&ObjectPos::OnUpdate, this, _1));
    }

    // Called by the world update start event
    public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
      math::Pose pose = this->model->GetWorldPose();
      msgs::Pose poseMsg = msgs::Convert(pose);
      this->posePub->Publish(poseMsg);
    }

    private: physics::ModelPtr model;

    private: transport::PublisherPtr posePub;
    // Pointer to the model
    private: physics::WorldPtr world;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_WORLD_PLUGIN(ObjectPos)
}