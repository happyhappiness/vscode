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
    }

    PROF_stop(SignalEngine_checkEvents);
    return EVENT_IDLE;
}