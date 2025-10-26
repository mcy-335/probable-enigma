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
        if(cmd == 'M'){
            std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
            
            cmder->DoOperate(*this);
        }
        else if(cmd == 'L'){
            std::unique_ptr<TurnLeftCommand> cmder = std::make_unique<TurnLeftCommand>();
            cmder->DoOperate(*this);
        }
        else if(cmd == 'R'){        
            std::unique_ptr<TurnRightCommand> cmder = std::make_unique<TurnRightCommand>();
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