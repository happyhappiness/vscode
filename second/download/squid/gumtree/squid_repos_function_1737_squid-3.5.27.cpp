void
EventLoop::run()
{
    prepareToRun();

    assert(!Running);
    Running = this;

    while (!runOnce());

    Running = NULL;
}