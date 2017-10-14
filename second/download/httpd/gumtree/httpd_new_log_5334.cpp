ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00263)
                 "pid %" APR_PID_T_FMT " taking over scoreboard slot from "
                 "%" APR_PID_T_FMT "%s",
                 newpid,
                 ap_scoreboard_image->parent[slot].pid,
                 ap_scoreboard_image->parent[slot].quiescing ?
                 " (quiescing)" : "");