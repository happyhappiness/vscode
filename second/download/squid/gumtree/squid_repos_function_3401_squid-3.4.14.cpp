void
fatal_dump(const char *message)
{
    failure_notify = NULL;
    releaseServerSockets();

    if (message)
        fatal_common(message);

    /*
     * Call leave_suid() here to make sure that swap.state files
     * are written as the effective user, rather than root.  Squid
     * may take on root privs during reconfigure.  If squid.conf
     * contains a "Bungled" line, fatal() will be called when the
     * process still has root privs.
     */
    leave_suid();

    if (opt_catch_signals)
        storeDirWriteCleanLogs(0);

    abort();
}