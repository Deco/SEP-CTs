#include <boost/bind.hpp>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <stdio.h>

namespace gazebo
{
  class CameraPush : public ModelPlugin
  {
    public: void cb(const boost::shared_ptr<msgs::Pose const> &_msg)
    {
      math::Pose pose = msgs::Convert(*_msg);
      std::cout << pose.pos.y << std::endl;
    }

    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr /*_sdf*/)
    {
      // Store the pointer to the model
      this->model = _parent;
      transport::NodePtr node(new transport::Node());
      node->Init();
      //this->sub = node->Subscribe("~/world_stats", &CameraPush::cb, this);
      this->sub = node->Subscribe<msgs::Pose>("~/test", &CameraPush::cb, this);

      this->updateConnection = event::Events::ConnectWorldUpdateBegin(
          boost::bind(&CameraPush::OnUpdate, this, _1));
    }

    // Called by the world update start event
    public: void OnUpdate(const common::UpdateInfo & /*_info*/)
    {
     

    }

    private: transport::SubscriberPtr sub;

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(CameraPush)
}