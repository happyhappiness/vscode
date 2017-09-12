int redisSupervisedUpstart(void) {
    const char *upstart_job = getenv("UPSTART_JOB");

    if (!upstart_job) {
        serverLog(REDIS_WARNING,
                "upstart supervision requested, but UPSTART_JOB not found");
        return 0;
    }

    serverLog(REDIS_NOTICE, "supervised by upstart, will stop to signal readyness");
    raise(SIGSTOP);
    unsetenv("UPSTART_JOB");
    return 1;
}