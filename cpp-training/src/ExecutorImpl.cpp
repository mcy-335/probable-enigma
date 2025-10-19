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
                break;
        }
    }
    
    
}
Pose ExecutorImpl::Query() const noexcept
{
return pose;
}
}