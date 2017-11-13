static void set_signals(void)
{
#ifndef NO_USE_SIGACTION
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (!one_process) {
        sa.sa_handler = sig_coredump;
#if defined(SA_ONESHOT)
        sa.sa_flags = SA_ONESHOT;
#elif defined(SA_RESETHAND)
        sa.sa_flags = SA_RESETHAND;
#endif
        if (sigaction(SIGSEGV, &sa, NULL) < 0)
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                         "sigaction(SIGSEGV)");
#ifdef SIGBUS
        if (sigaction(SIGBUS, &sa, NULL) < 0)
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                         "sigaction(SIGBUS)");
#endif
#ifdef SIGABORT
        if (sigaction(SIGABORT, &sa, NULL) < 0)
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                         "sigaction(SIGABORT)");
#endif
#ifdef SIGABRT
        if (sigaction(SIGABRT, &sa, NULL) < 0)
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                         "sigaction(SIGABRT)");
#endif
#ifdef SIGILL
        if (sigaction(SIGILL, &sa, NULL) < 0)
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                         "sigaction(SIGILL)");
#endif
        sa.sa_flags = 0;
    }
    sa.sa_handler = sig_term;
    if (sigaction(SIGTERM, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(SIGTERM)");
#ifdef SIGINT
    if (sigaction(SIGINT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(SIGINT)");
#endif
#ifdef SIGXCPU
    sa.sa_handler = SIG_DFL;
    if (sigaction(SIGXCPU, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(SIGXCPU)");
#endif
#ifdef SIGXFSZ
    sa.sa_handler = SIG_DFL;
    if (sigaction(SIGXFSZ, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(SIGXFSZ)");
#endif
#ifdef SIGPIPE
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(SIGPIPE)");
#endif

    /* we want to ignore HUPs and AP_SIG_GRACEFUL while we're busy 
     * processing one */
    sigaddset(&sa.sa_mask, SIGHUP);
    sigaddset(&sa.sa_mask, AP_SIG_GRACEFUL);
    sa.sa_handler = restart;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(SIGHUP)");
    if (sigaction(AP_SIG_GRACEFUL, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, 
                     "sigaction(" AP_SIG_GRACEFUL_STRING ")");
#else
    if (!one_process) {
        apr_signal(SIGSEGV, sig_coredump);
#ifdef SIGBUS
        apr_signal(SIGBUS, sig_coredump);
#endif /* SIGBUS */
#ifdef SIGABORT
        apr_signal(SIGABORT, sig_coredump);
#endif /* SIGABORT */
#ifdef SIGABRT
        apr_signal(SIGABRT, sig_coredump);
#endif /* SIGABRT */
#ifdef SIGILL
        apr_signal(SIGILL, sig_coredump);
#endif /* SIGILL */
#ifdef SIGXCPU
        apr_signal(SIGXCPU, SIG_DFL);
#endif /* SIGXCPU */
#ifdef SIGXFSZ
        apr_signal(SIGXFSZ, SIG_DFL);
#endif /* SIGXFSZ */
    }

    apr_signal(SIGTERM, sig_term);
#ifdef SIGHUP
    apr_signal(SIGHUP, restart);
#endif /* SIGHUP */
#ifdef AP_SIG_GRACEFUL
    apr_signal(AP_SIG_GRACEFUL, restart);
#endif /* AP_SIG_GRACEFUL */
#ifdef SIGPIPE
    apr_signal(SIGPIPE, SIG_IGN);
#endif /* SIGPIPE */

#endif
}