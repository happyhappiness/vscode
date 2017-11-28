void
death(int sig)
{
    if (sig == SIGSEGV)
        fprintf(debug_log, "FATAL: Received Segment Violation...dying.\n");
    else if (sig == SIGBUS)
        fprintf(debug_log, "FATAL: Received Bus Error...dying.\n");
    else
        fprintf(debug_log, "FATAL: Received signal %d...dying.\n", sig);

#ifdef PRINT_STACK_TRACE
#ifdef _SQUID_HPUX_
    {
        extern void U_STACK_TRACE(void);	/* link with -lcl */
        fflush(debug_log);
        dup2(fileno(debug_log), 2);
        U_STACK_TRACE();
    }

#endif /* _SQUID_HPUX_ */
#if defined(_SQUID_SOLARIS_) && HAVE_LIBOPCOM_STACK
    {				/* get ftp://opcom.sun.ca/pub/tars/opcom_stack.tar.gz and */
        extern void opcom_stack_trace(void);	/* link with -lopcom_stack */
        fflush(debug_log);
        dup2(fileno(debug_log), fileno(stdout));
        opcom_stack_trace();
        fflush(stdout);
    }

#endif /* _SQUID_SOLARIS_  and HAVE_LIBOPCOM_STACK */
#if HAVE_BACKTRACE_SYMBOLS_FD
    {
        static void *(callarray[8192]);
        int n;
        n = backtrace(callarray, 8192);
        backtrace_symbols_fd(callarray, n, fileno(debug_log));
    }

#endif
#endif /* PRINT_STACK_TRACE */

#if SA_RESETHAND == 0 && !defined(_SQUID_MSWIN_)
    signal(SIGSEGV, SIG_DFL);

    signal(SIGBUS, SIG_DFL);

    signal(sig, SIG_DFL);

#endif

    releaseServerSockets();

    storeDirWriteCleanLogs(0);

    if (!shutting_down) {
        PrintRusage();

        dumpMallocStats();
    }

    if (squid_curtime - SQUID_RELEASE_TIME < 864000) {
        /* skip if more than 10 days old */

        if (Config.adminEmail)
            mail_warranty();

        puts(dead_msg());
    }

    if (shutting_down)
        exit(1);

    abort();
}