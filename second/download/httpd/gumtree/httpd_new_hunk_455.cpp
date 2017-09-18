         */
        if (unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf,
                         "killpg SIGTERM");
        }
        ap_reclaim_child_processes(1);      /* Start with SIGTERM */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0,
                     ap_server_conf, "SIGHUP received.  Attempting to restart");
    }
    return 0;
}

/* This really should be a post_config hook, but the error log is already
