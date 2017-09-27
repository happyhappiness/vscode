            }

            ++total_non_dead;
            last_non_dead = i;
        }
    }
    retained->max_daemons_limit = last_non_dead + 1;
    if (idle_count > ap_daemons_max_free) {
        /* kill off one child... we use the pod because that'll cause it to
         * shut down gracefully, in case it happened to pick up a request
         * while we were counting
         */
        ap_mpm_pod_signal(pod);
        retained->idle_spawn_rate = 1;
    }
    else if (idle_count < ap_daemons_min_free) {
        /* terminate the free list */
        if (free_length == 0) {
            /* only report this condition once */
            if (!retained->maxclients_reported) {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00161)
                            "server reached MaxRequestWorkers setting, consider"
                            " raising the MaxRequestWorkers setting");
                retained->maxclients_reported = 1;
            }
            retained->idle_spawn_rate = 1;
        }
        else {
            if (retained->idle_spawn_rate >= 8) {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00162)
                    "server seems busy, (you may need "
                    "to increase StartServers, or Min/MaxSpareServers), "
                    "spawning %d children, there are %d idle, and "
                    "%d total children", retained->idle_spawn_rate,
                    idle_count, total_non_dead);
            }
            for (i = 0; i < free_length; ++i) {
                make_child(ap_server_conf, free_slots[i]);
            }
            /* the next time around we want to spawn twice as many if this
             * wasn't good enough, but not if we've just done a graceful
             */
            if (retained->hold_off_on_exponential_spawning) {
                --retained->hold_off_on_exponential_spawning;
            }
            else if (retained->idle_spawn_rate < MAX_SPAWN_RATE) {
                retained->idle_spawn_rate *= 2;
            }
        }
    }
    else {
        retained->idle_spawn_rate = 1;
    }
}

/*****************************************************************
 * Executive routines.
 */
