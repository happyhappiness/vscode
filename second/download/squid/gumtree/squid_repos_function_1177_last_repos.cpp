int
SignalEngine::checkEvents(int)
{
    PROF_start(SignalEngine_checkEvents);

    if (do_reconfigure)
        mainReconfigureStart();
    else if (do_rotate)
        mainRotate();
    else if (do_shutdown)
        doShutdown(do_shutdown > 0 ? (int) Config.shutdownLifetime : 0);
    if (do_handle_stopped_child)
        handleStoppedChild();
    PROF_stop(SignalEngine_checkEvents);
    return EVENT_IDLE;
}