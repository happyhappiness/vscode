        return 0;
    }

    serverLog(LL_NOTICE, "supervised by upstart, will stop to signal readyness");
    raise(SIGSTOP);
    unsetenv("UPSTART_JOB");
    return 1;
