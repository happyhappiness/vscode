};

class SignalEngine: public AsyncEngine
{

public:
    SignalEngine(EventLoop &evtLoop) : loop(evtLoop) {}
    virtual int checkEvents(int timeout);

private:
    static void StopEventLoop(void * data) {
        static_cast<SignalEngine *>(data)->loop.stop();
    }

    void doShutdown(time_t wait);

    EventLoop &loop;
};

int
SignalEngine::checkEvents(int timeout)
{
    PROF_start(SignalEngine_checkEvents);

    if (do_reconfigure) {
        mainReconfigureStart();
        do_reconfigure = 0;
    } else if (do_rotate) {
        mainRotate();
        do_rotate = 0;
    } else if (do_shutdown) {
        doShutdown(do_shutdown > 0 ? (int) Config.shutdownLifetime : 0);
        do_shutdown = 0;
