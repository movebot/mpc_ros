 /** include the libraries you need in your planner here */
 /** for global path planner interface */
 #include <ros/ros.h>
 #include <costmap_2d/costmap_2d_ros.h>
 #include <costmap_2d/costmap_2d.h>
 #include <nav_core/base_global_planner.h>
 #include <geometry_msgs/PoseStamped.h>
 #include <angles/angles.h>
 #include <base_local_planner/world_model.h>
 #include <base_local_planner/costmap_model.h>

 #include <nav_msgs/Odometry.h>
 #include <nav_msgs/Path.h>
#include <tf/transform_listener.h>

 using std::string;

 #ifndef GLOBAL_PLANNER_CPP
 #define GLOBAL_PLANNER_CPP

 namespace global_planner {

 class GeonPlanner : public nav_core::BaseGlobalPlanner {
 public:

    GeonPlanner();
    GeonPlanner(std::string name, costmap_2d::Costmap2DROS* costmap_ros);

    /** overridden classes from interface nav_core::BaseGlobalPlanner **/
    void initialize(std::string name, costmap_2d::Costmap2DROS* costmap_ros);
    bool makePlan(const geometry_msgs::PoseStamped& start,
                const geometry_msgs::PoseStamped& goal,
                std::vector<geometry_msgs::PoseStamped>& plan
               );
  
    ros::NodeHandle _nh;
    ros::Publisher _pub_globalpath;
    ros::Subscriber _sub_odom, _sub_get_path;
  
    nav_msgs::Odometry _odom;
    nav_msgs::Path _desired_path;
    tf::TransformListener _tf_listener;

    double _waypointsDist;  //minimum distance between points of path
    int min_idx; //nearest point
    double _pathLength;

    void odomCB(const nav_msgs::Odometry::ConstPtr& odomMsg);
    void desiredPathCB(const nav_msgs::Path::ConstPtr& pathMsg);

  };
 };
 #endif

