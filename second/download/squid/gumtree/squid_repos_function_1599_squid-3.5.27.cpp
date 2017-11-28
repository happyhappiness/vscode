static int
checkRunningPid(void)
{
    // master process must start alone, but its kids processes may co-exist
    if (!IamMasterProcess())
        return 0;

    pid_t pid;

    if (!debug_log)
        debug_log = stderr;

    pid = readPidFile();

    if (pid < 2)
        return 0;

    if (kill(pid, 0) < 0)
        return 0;

    debugs(0, DBG_CRITICAL, "Squid is already running!  Process ID " <<  pid);

    return 1;
}