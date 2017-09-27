#else
    sa.sa_flags = 0;
#endif

    sa.sa_handler = sig_coredump;
    if (sigaction(SIGSEGV, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGSEGV)");
#ifdef SIGBUS
    if (sigaction(SIGBUS, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGBUS)");
#endif
#ifdef SIGABORT
    if (sigaction(SIGABORT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABORT)");
#endif
#ifdef SIGABRT
    if (sigaction(SIGABRT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABRT)");
#endif
#ifdef SIGILL
    if (sigaction(SIGILL, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGILL)");
#endif
#ifdef SIGFPE
    if (sigaction(SIGFPE, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGFPE)");
#endif

#else /* NO_USE_SIGACTION */

    apr_signal(SIGSEGV, sig_coredump);
#ifdef SIGBUS
