#include "ExecutorImpl.hpp"
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for(char cmd:commands){
        switch(cmd){
            case 'M':
                Move();
                break;
            case 'L':
                switch(pose.heading){
                    case 'E':
                        pose.heading = 'N';
                        break;
                    case 'N':
                        pose.heading = 'W';
                        break;
                    case 'W':
                        pose.heading = 'S';
                        break;
                    case 'S':
                        pose.heading = 'E';
                        break;
                }
                break;
            case 'R':
                switch(pose.heading){   
                    case 'N':
                        pose.heading = 'E';
                        break;
                    case 'E':
                        pose.heading = 'S';
                        break;
                    case 'S':
                        pose.heading = 'W';
                        break;
                    case 'W':
                        pose.heading = 'N';
                        break;
                }
                break;
        }
    }
    
    
}
void ExecutorImpl::Move() noexcept
{
   switch(pose.heading){
        case 'N':
            pose.y += 1;
            break;
        case 'S':
            pose.y -= 1;
            break;
        case 'E':
            pose.x += 1;
            break;
        case 'W':
            pose.x -= 1;
            break;
    }
}
Pose ExecutorImpl::Query() const noexcept
{
return pose;
}
}