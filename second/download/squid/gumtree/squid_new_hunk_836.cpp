};

class SignalEngine: public AsyncEngine
{

public:
    virtual int checkEvents(int timeout);

private:
    static void StopEventLoop(void *) {
        if (EventLoop::Running)
            EventLoop::Running->stop();
    }

    static void FinalShutdownRunners(void *) {
        RunRegisteredHere(RegisteredRunner::endingShutdown);

        // XXX: this should be a Runner.
#if USE_AUTH
        /* detach the auth components (only do this on full shutdown) */
        Auth::Scheme::FreeAll();
#endif

        eventAdd("SquidTerminate", &StopEventLoop, NULL, 0, 1, false);
    }

    void doShutdown(time_t wait);
};

int
SignalEngine::checkEvents(int timeout)
{
    PROF_start(SignalEngine_checkEvents);

    if (do_reconfigure) {
        if (!reconfiguring && configured_once) {
            mainReconfigureStart();
            do_reconfigure = 0;
        } // else wait until previous reconfigure is done
    } else if (do_rotate) {
        mainRotate();
        do_rotate = 0;
    } else if (do_shutdown) {
        doShutdown(do_shutdown > 0 ? (int) Config.shutdownLifetime : 0);
        do_shutdown = 0;
