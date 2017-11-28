void
SignalEngine::doShutdown(time_t wait)
{
    if (AvoidSignalAction("shutdown", do_shutdown))
        return;

    debugs(1, DBG_IMPORTANT, "Preparing for shutdown after " << statCounter.client_http.requests << " requests");
    debugs(1, DBG_IMPORTANT, "Waiting " << wait << " seconds for active connections to finish");

#if KILL_PARENT_OPT
    if (!IamMasterProcess() && !parentKillNotified && ShutdownSignal > 0 && parentPid > 1) {
        debugs(1, DBG_IMPORTANT, "Killing master process, pid " << parentPid);
        if (kill(parentPid, ShutdownSignal) < 0) {
            int xerrno = errno;
            debugs(1, DBG_IMPORTANT, "kill " << parentPid << ": " << xstrerr(xerrno));
        }
        parentKillNotified = true;
    }
#endif

    if (shutting_down) {
#if !KILL_PARENT_OPT
        // Already a shutdown signal has received and shutdown is in progress.
        // Shutdown as soon as possible.
        wait = 0;
#endif
    } else {
        shutting_down = 1;

        /* run the closure code which can be shared with reconfigure */
        serverConnectionsClose();

        RunRegisteredHere(RegisteredRunner::startShutdown);
    }

#if USE_WIN32_SERVICE
    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, (wait + 1) * 1000);
#endif

    eventAdd("SquidShutdown", &FinalShutdownRunners, this, (double) (wait + 1), 1, false);
}