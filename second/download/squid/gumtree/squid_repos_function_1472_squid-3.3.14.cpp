void
shut_down(int sig)
{
    do_shutdown = sig == SIGINT ? -1 : 1;
    ShutdownSignal = sig;
#ifdef SIGTTIN

    if (SIGTTIN == sig)
        shutdown_status = 1;

#endif

    const pid_t ppid = getppid();

    if (!IamMasterProcess() && ppid > 1) {
        // notify master that we are shutting down
        if (kill(ppid, SIGUSR1) < 0)
            debugs(1, DBG_IMPORTANT, "Failed to send SIGUSR1 to master process,"
                   " pid " << ppid << ": " << xstrerror());
    }

#if !_SQUID_WINDOWS_
#if KILL_PARENT_OPT

    if (!IamMasterProcess() && ppid > 1) {
        debugs(1, DBG_IMPORTANT, "Killing master process, pid " << ppid);

        if (kill(ppid, sig) < 0)
            debugs(1, DBG_IMPORTANT, "kill " << ppid << ": " << xstrerror());
    }

#endif /* KILL_PARENT_OPT */
#if SA_RESETHAND == 0
    signal(SIGTERM, SIG_DFL);

    signal(SIGINT, SIG_DFL);

#endif
#endif
}