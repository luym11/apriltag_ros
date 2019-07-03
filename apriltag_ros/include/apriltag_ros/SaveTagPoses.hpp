#ifndef SaveTagPoses_HPP
#define SaveTagPoses_HPP
#include <tf/transform_listener.h>
#include <fstream>

class SaveTagPoses{
    public:
        SaveTagPoses();
        tf::TransformListener listener; 
};
#endif