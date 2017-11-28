void
EventLoop::run()
{
    prepareToRun();

    while (!runOnce());
}