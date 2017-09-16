	    ap_log_error(APLOG_MARK, APLOG_WARNING, server_conf, "sigaction(SIGABORT)");

#endif

#ifdef SIGABRT

	if (sigaction(SIGABRT, &sa, NULL) < 0)

	    ap_log_error(APLOG_MARK, APLOG_WARNING, server_conf, "sigaction(SIGABRT)");

#endif

#ifdef SIGILL

	if (sigaction(SIGILL, &sa, NULL) < 0)

	    ap_log_error(APLOG_MARK, APLOG_WARNING, server_conf, "sigaction(SIGILL)");

#endif

	sa.sa_flags = 0;

    }

    sa.sa_handler = sig_term;

    if (sigaction(SIGTERM, &sa, NULL) < 0)

	ap_log_error(APLOG_MARK, APLOG_WARNING, server_conf, "sigaction(SIGTERM)");

#ifdef SIGINT

