#pragma once
#include "Executor.hpp"
namespace adas
{
class ExecutorImpl final : public Executor
{
public:
explicit ExecutorImpl(const Pose& pose) noexcept;
~ExecutorImpl() noexcept = default;
 ExecutorImpl(const ExecutorImpl&) = delete;
ExecutorImpl& operator=(const ExecutorImpl&) = delete;
public:
void Execute(const std::string& command) noexcept override;
Pose Query(void) const noexcept override;
private:
class MoveCommand final
{
public:
void DoOperate(ExecutorImpl& executor) const noexcept
{
    executor.Move();
}
};
class TurnLeftCommand final
{
    public:
    void DoOperate(ExecutorImpl& executor) const noexcept
    {
        executor.TurnLeft();
    }
};
class TurnRightCommand final  
{
    public:
    void DoOperate(ExecutorImpl& executor) const noexcept
    {
        executor.TurnRight();
    }
};
void Move(void) noexcept;
void TurnLeft(void) noexcept;
void TurnRight(void) noexcept;
Pose pose;
};
}