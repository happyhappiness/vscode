static void StopEventLoop(void *) {
        if (EventLoop::Running)
            EventLoop::Running->stop();
    }