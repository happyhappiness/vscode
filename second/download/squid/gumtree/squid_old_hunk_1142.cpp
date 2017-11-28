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
    }
    BroadcastSignalIfAny(DebugSignal);
    BroadcastSignalIfAny(RotateSignal);
    BroadcastSignalIfAny(ReconfigureSignal);
    BroadcastSignalIfAny(ShutdownSignal);

    PROF_stop(SignalEngine_checkEvents);
    return EVENT_IDLE;
}

void
SignalEngine::doShutdown(time_t wait)
{
    debugs(1, DBG_IMPORTANT, "Preparing for shutdown after " << statCounter.client_http.requests << " requests");
    debugs(1, DBG_IMPORTANT, "Waiting " << wait << " seconds for active connections to finish");

    shutting_down = 1;

#if USE_WIN32_SERVICE
    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, (wait + 1) * 1000);
#endif

    /* run the closure code which can be shared with reconfigure */
    serverConnectionsClose();
    RunRegisteredHere(RegisteredRunner::startShutdown);
    eventAdd("SquidShutdown", &FinalShutdownRunners, this, (double) (wait + 1), 1, false);
}

static void
usage(void)
{
    fprintf(stderr,
            "Usage: %s [-cdhvzCFNRVYX] [-n name] [-s | -l facility] [-f config-file] [-[au] port] [-k signal]"
#if USE_WIN32_SERVICE
            "[-ir] [-O CommandLine]"
#endif
            "\n"
            "       -a port   Specify HTTP port number (default: %d).\n"
            "       -d level  Write debugging to stderr also.\n"
            "       -f file   Use given config-file instead of\n"
            "                 %s\n"
            "       -h        Print help message.\n"
#if USE_WIN32_SERVICE
            "       -i        Installs as a Windows Service (see -n option).\n"
#endif
            "       -k reconfigure|rotate|shutdown|"
#ifdef SIGTTIN
            "restart|"
