#include <iostream>
#include <fstream>
#include "ros/ros.h"
#include <math.h>
#include "std_msgs/String.h"
#include <tf/transform_listener.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/WrenchStamped.h>
#include <ins_write_file/Num3.h>
int i=0,j=1;


void write_accel_val( ins_write_file::Num3 custom_var)
{

  float accelx,accely,accelz,pos_x,pos_y,pos_z;
  double accel_tot;
  accelx=custom_var.body_wrench.wrench.force.x;
  accely=custom_var.body_wrench.wrench.force.y;
  accelz=custom_var.body_wrench.wrench.force.z;
  pos_x=custom_var.body_pos.wrench.force.x;
  pos_y=custom_var.body_pos.wrench.force.y;
  pos_z=custom_var.body_pos.wrench.force.z;
  accel_tot=sqrt(pow(accelx,2)+pow(accely,2)+pow(accelz,2));
  printf("\n%f",accel_tot);
  std::ofstream myfile;
  //tf::Vector3 pos;
  //pos=transform.getOrigin();
  //float accelx,accely,accelz;
  ros::Time t;
  t=ros::Time::now();
  myfile.open ("/home/aimlabx/Desktop/insertion_link_accel_values.csv",std::ios_base::app);
  //myfile << "This is the first cell in the first column.\n";
  if(i>10)
  {
    myfile<<j<<",accel x value,"<<accelx<<",accel y value,"<<accely<<",accel z value,"<<accelz<<",pos_x,"<<pos_x<<",pos_y,"<<pos_y<<",pos_z,"<<pos_z<<",time,"<<t<<"\n";
    j++;
  }
  else i++;
  myfile.close();

}


int main(int argc, char **argv)
{



  ros::init(argc, argv, "listener_ins");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("/wrench_visualization/wrench_insertion", 1000, write_accel_val);
  ros::spin();
  return 0;
}


