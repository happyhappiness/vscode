ap_log_error(APLOG_MARK, APLOG_CRIT, APR_EBADPATH, NULL,
                         "Fatal error: Invalid Scoreboard path %s",
                         ap_scoreboard_fname);