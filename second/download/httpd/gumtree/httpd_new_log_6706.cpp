ap_log_error(APLOG_MARK, APLOG_TRACE5, 0, ap_server_conf,
                         "Not shutting down child: total daemons %d / "
                         "active limit %d / ServerLimit %d",
                         retained->total_daemons, active_daemons_limit,
                         server_limit);