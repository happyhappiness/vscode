	if (sigaction(SIGABRT, &sa, NULL) < 0)
	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGABRT)");
	if (sigaction(SIGILL, &sa, NULL) < 0)
	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGILL)");
	sa.sa_flags = 0;
    }

    /* These next two are handled by sig_term */
    sa.sa_handler = sig_term;
    if (sigaction(SIGTERM, &sa, NULL) < 0)
	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGTERM)");
    if (sigaction(SIGINT, &sa, NULL) < 0)
        ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGINT)");

    /* We ignore SIGPIPE */
    sa.sa_handler = SIG_IGN;
    if (sigaction(SIGPIPE, &sa, NULL) < 0)
    	ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGPIPE)");

    /* we want to ignore HUPs and AP_SIG_GRACEFUL while we're busy
     * processing one */
    sigaddset(&sa.sa_mask, SIGHUP);
    sigaddset(&sa.sa_mask, AP_SIG_GRACEFUL);
    sa.sa_handler = restart;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    	ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "sigaction(SIGHUP)");
