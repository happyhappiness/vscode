bool
EventLoop::dispatchCalls()
{
    bool dispatchedSome = AsyncCallQueue::Instance().fire();
    return dispatchedSome;
}