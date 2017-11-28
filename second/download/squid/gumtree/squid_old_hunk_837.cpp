#if USE_WIN32_SERVICE
    WIN32_svcstatusupdate(SERVICE_STOP_PENDING, (wait + 1) * 1000);
#endif

    /* run the closure code which can be shared with reconfigure */
    serverConnectionsClose();
#if USE_AUTH
    /* detach the auth components (only do this on full shutdown) */
    Auth::Scheme::FreeAll();
#endif
    eventAdd("SquidShutdown", &StopEventLoop, this, (double) (wait + 1), 1, false);
}

static void
usage(void)
{
    fprintf(stderr,
#if USE_WIN32_SERVICE
            "Usage: %s [-cdhirvzCFNRVYX] [-s | -l facility] [-f config-file] [-[au] port] [-k signal] [-n name] [-O CommandLine]\n"
#else
            "Usage: %s [-cdhvzCFNRVYX] [-s | -l facility] [-f config-file] [-[au] port] [-k signal]\n"
#endif
            "       -a port   Specify HTTP port number (default: %d).\n"
            "       -d level  Write debugging to stderr also.\n"
            "       -f file   Use given config-file instead of\n"
            "                 %s\n"
            "       -h        Print help message.\n"
#if USE_WIN32_SERVICE
