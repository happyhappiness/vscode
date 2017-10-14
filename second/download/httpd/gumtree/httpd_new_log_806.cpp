ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
              "proxy: ap_get_scoreboard_lb(%d) failed for worker %s",
              worker->id, worker->name);