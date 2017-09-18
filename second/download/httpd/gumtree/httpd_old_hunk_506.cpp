    else {
	/* Kill 'em off */
	if (unixd_killpg(getpgrp(), SIGHUP) < 0) {
	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "killpg SIGHUP");
	}
	ap_reclaim_child_processes(0);		/* Not when just starting up */
	ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_NOTICE, 0, ap_server_conf,
		    "SIGHUP received.  Attempting to restart");
    }

    return 0;
}

