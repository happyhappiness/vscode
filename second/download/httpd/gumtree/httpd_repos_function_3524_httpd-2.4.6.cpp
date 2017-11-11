static void perform_idle_server_maintenance(apr_pool_t *p)
{
    int i;
    int idle_count;
    worker_score *ws;
    int free_length;
    int free_slots[MAX_SPAWN_RATE];
    int last_non_dead;
    int total_non_dead;

    /* initialize the free_list */
    free_length = 0;

    idle_count = 0;
    last_non_dead = -1;
    total_non_dead = 0;

    for (i = 0; i < ap_daemons_limit; ++i) {
        int status;

        if (i >= retained->max_daemons_limit && free_length == retained->idle_spawn_rate)
            break;
        ws = &ap_scoreboard_image->servers[i][0];
        status = ws->status;
        if (status == SERVER_DEAD) {
            /* try to keep children numbers as low as possible */
            if (free_length < retained->idle_spawn_rate) {
                free_slots[free_length] = i;
                ++free_length;
            }
        }
        else {
            /* We consider a starting server as idle because we started it
             * at least a cycle ago, and if it still hasn't finished starting
             * then we're just going to swamp things worse by forking more.
             * So we hopefully won't need to fork more if we count it.
             * This depends on the ordering of SERVER_READY and SERVER_STARTING.
             */
            if (status <= SERVER_READY) {
                ++ idle_count;
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