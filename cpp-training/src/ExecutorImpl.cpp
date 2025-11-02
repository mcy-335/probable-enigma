#include "ExecutorImpl.hpp"
#include <memory>
#include "Command.hpp"
#include<unordered_map>
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const std::unordered_map<char, std::function<void(PoseHandler & poseHandler)>> cmderMap {
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'F', FastCommand()},
    };
    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);
            if (it != cmderMap.end()) {
                it->second(poseHandler);
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
void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}
bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}
Pose ExecutorImpl::Query() const noexcept
{
return poseHandler.Query();
}
}