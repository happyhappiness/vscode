                             "setting");
                retained->maxclients_reported = 1;
            }
            retained->idle_spawn_rate[child_bucket] = 1;
        }
        else if (free_length == 0) { /* scoreboard is full, can't fork */
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO()
                         "scoreboard is full, not at MaxRequestWorkers."
                         "Increase ServerLimit.");
            retained->idle_spawn_rate[child_bucket] = 1;
        }
        else {
            if (free_length > retained->idle_spawn_rate[child_bucket]) {
