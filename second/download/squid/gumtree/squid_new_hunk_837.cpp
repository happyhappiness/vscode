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
