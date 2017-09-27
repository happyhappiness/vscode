#ifdef SIGPIPE
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL) < 0)
	ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGPIPE)");
#endif

    /* we want to ignore HUPs and AP_SIG_GRACEFUL while we're busy 
     * processing one */
    sigaddset(&sa.sa_mask, SIGHUP);
    sigaddset(&sa.sa_mask, AP_SIG_GRACEFUL);
    sa.sa_handler = restart;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
	ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGHUP)");
    if (sigaction(AP_SIG_GRACEFUL, &sa, NULL) < 0)
