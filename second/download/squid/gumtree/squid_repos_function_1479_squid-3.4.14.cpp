static void StopEventLoop(void * data) {
        static_cast<SignalEngine *>(data)->loop.stop();
    }