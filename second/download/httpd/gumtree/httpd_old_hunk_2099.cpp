        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGABRT)");
#endif
#ifdef SIGILL
    if (sigaction(SIGILL, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, s, "sigaction(SIGILL)");
#endif

#else /* NO_USE_SIGACTION */

    apr_signal(SIGSEGV, sig_coredump);
#ifdef SIGBUS
    apr_signal(SIGBUS, sig_coredump);
