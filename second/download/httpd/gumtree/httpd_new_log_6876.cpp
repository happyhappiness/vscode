ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(03455)
                 "BUG: Scoreboard slot %d should be empty but is "
                 "in use by pid %" APR_PID_T_FMT,
                 slot, ap_scoreboard_image->parent[slot].pid);