void
shut_down(int sig)
{
    do_shutdown = sig == SIGINT ? -1 : 1;
#ifdef SIGTTIN

    if (SIGTTIN == sig)
        shutdown_status = 1;

#endif
#ifndef _SQUID_MSWIN_
#ifdef KILL_PARENT_OPT

    if (getppid() > 1) {
        debugs(1, 1, "Killing master process, pid " << getppid());

        if (kill(getppid(), sig) < 0)
            debugs(1, 1, "kill " << getppid() << ": " << xstrerror());
    }

#endif
#if SA_RESETHAND == 0
    signal(SIGTERM, SIG_DFL);

    signal(SIGINT, SIG_DFL);

#endif
#endif
}