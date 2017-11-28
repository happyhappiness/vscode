static void
masterCheckAndBroadcastSignals()
{
    // if (do_reconfigure)
    //     TODO: hot-reconfiguration of the number of kids and PID file location

    if (do_shutdown)
        shutting_down = 1;

    BroadcastSignalIfAny(DebugSignal);
    BroadcastSignalIfAny(RotateSignal);
    BroadcastSignalIfAny(ReconfigureSignal);
    BroadcastSignalIfAny(ShutdownSignal);
}