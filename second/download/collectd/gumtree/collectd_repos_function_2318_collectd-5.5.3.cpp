static int notify_upstart (void)
{
    const char  *upstart_job = getenv("UPSTART_JOB");

    if (upstart_job == NULL)
        return 0;

    if (strcmp(upstart_job, "collectd") != 0)
        return 0;

    WARNING ("supervised by upstart, will stop to signal readyness");
    raise(SIGSTOP);
    unsetenv("UPSTART_JOB");

    return 1;
}