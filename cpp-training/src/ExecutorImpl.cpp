#include "ExecutorImpl.hpp"
#include <memory>
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
        std::unique_ptr<ICommand> cmder;
        if(cmd == 'M'){
            cmder = std::make_unique<MoveCommand>();
        }
        else if(cmd == 'L'){
            cmder = std::make_unique<TurnLeftCommand>();
        }
        else if(cmd == 'R'){        
            cmder = std::make_unique<TurnRightCommand>();
        }
        if(cmder){
            cmder->DoOperate(*this);
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
void ExecutorImpl::TurnLeft() noexcept
{
    switch(pose.heading){
        case 'N':
            pose.heading = 'W';
            break;
        case 'W':
            pose.heading = 'S';
            break;
        case 'S':
            pose.heading = 'E';
            break;
        case 'E':
            pose.heading = 'N';
            break;
    }
}
void ExecutorImpl::TurnRight() noexcept
{
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
}
Pose ExecutorImpl::Query() const noexcept
{
return pose;
}
}