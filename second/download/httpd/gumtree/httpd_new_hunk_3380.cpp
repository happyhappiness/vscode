            }
        }
    }
    else {
        /* Kill 'em off */
        if (ap_unixd_killpg(getpgrp(), SIGHUP) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00172) "killpg SIGHUP");
        }
        ap_reclaim_child_processes(0, /* Not when just starting up */
                                   prefork_note_child_killed);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00173)
                    "SIGHUP received.  Attempting to restart");
    }

    return OK;
}

