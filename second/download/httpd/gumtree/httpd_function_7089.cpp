static void perform_idle_server_maintenance(void)
{
    int i, j;
    int idle_thread_count;
    worker_score *ws;
    process_score *ps;
    int free_length;
    int totally_free_length = 0;
    int free_slots[MAX_SPAWN_RATE];
    int last_non_dead;
    int total_non_dead;
    int active_thread_count = 0;

    /* initialize the free_list */
    free_length = 0;

    idle_thread_count = 0;
    last_non_dead = -1;
    total_non_dead = 0;

    for (i = 0; i < ap_daemons_limit; ++i) {
        /* Initialization to satisfy the compiler. It doesn't know
         * that threads_per_child is always > 0 */
        int status = SERVER_DEAD;
        int any_dying_threads = 0;
        int any_dead_threads = 0;
        int all_dead_threads = 1;

        if (i >= retained->max_daemons_limit
            && totally_free_length == retained->idle_spawn_rate)
            /* short cut if all active processes have been examined and
             * enough empty scoreboard slots have been found
             */

            break;
        ps = &ap_scoreboard_image->parent[i];
        for (j = 0; j < threads_per_child; j++) {
            ws = &ap_scoreboard_image->servers[i][j];
            status = ws->status;

            /* XXX any_dying_threads is probably no longer needed    GLA */
            any_dying_threads = any_dying_threads ||
                (status == SERVER_GRACEFUL);
            any_dead_threads = any_dead_threads || (status == SERVER_DEAD);
            all_dead_threads = all_dead_threads &&
                (status == SERVER_DEAD || status == SERVER_GRACEFUL);

            /* We consider a starting server as idle because we started it
             * at least a cycle ago, and if it still hasn't finished starting
             * then we're just going to swamp things worse by forking more.
             * So we hopefully won't need to fork more if we count it.
             * This depends on the ordering of SERVER_READY and SERVER_STARTING.
             */
            if (ps->pid != 0) { /* XXX just set all_dead_threads in outer
                                   for loop if no pid?  not much else matters */
                if (status <= SERVER_READY && !ps->quiescing && !ps->not_accepting
                    && ps->generation == retained->my_generation)
                {
                    ++idle_thread_count;
                }
                if (status >= SERVER_READY && status < SERVER_GRACEFUL) {
                    ++active_thread_count;
                }
            }
        }
        if (any_dead_threads
            && totally_free_length < retained->idle_spawn_rate
            && free_length < MAX_SPAWN_RATE
            && (!ps->pid      /* no process in the slot */
                  || ps->quiescing)) {  /* or at least one is going away */
            if (all_dead_threads) {
                /* great! we prefer these, because the new process can
                 * start more threads sooner.  So prioritize this slot
                 * by putting it ahead of any slots with active threads.
                 *
                 * first, make room by moving a slot that's potentially still
                 * in use to the end of the array
                 */
                free_slots[free_length] = free_slots[totally_free_length];
                free_slots[totally_free_length++] = i;
            }
            else {
                /* slot is still in use - back of the bus
                 */
                free_slots[free_length] = i;
            }
            ++free_length;
        }
        /* XXX if (!ps->quiescing)     is probably more reliable  GLA */
        if (!any_dying_threads) {
            last_non_dead = i;
            ++total_non_dead;
        }
    }

    if (retained->sick_child_detected) {
        if (active_thread_count > 0) {
            /* some child processes appear to be working.  don't kill the
             * whole server.
             */
            retained->sick_child_detected = 0;
        }
        else {
            /* looks like a basket case.  give up.
             */
            shutdown_pending = 1;
            child_fatal = 1;
            ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                         ap_server_conf, APLOGNO(00483)
                         "No active workers found..."
                         " Apache is exiting!");
            /* the child already logged the failure details */
            return;
        }
    }

    retained->max_daemons_limit = last_non_dead + 1;

    if (idle_thread_count > max_spare_threads) {
        /* Kill off one child */
        ap_event_pod_signal(pod, TRUE);
        retained->idle_spawn_rate = 1;
    }
    else if (idle_thread_count < min_spare_threads) {
        /* terminate the free list */
        if (free_length == 0) { /* scoreboard is full, can't fork */

            if (active_thread_count >= ap_daemons_limit * threads_per_child) {
                if (!retained->maxclients_reported) {
                    /* only report this condition once */
                    ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00484)
                                 "server reached MaxRequestWorkers setting, "
                                 "consider raising the MaxRequestWorkers "
                                 "setting");
                    retained->maxclients_reported = 1;
                }
            }
            else {
                ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(00485)
                             "scoreboard is full, not at MaxRequestWorkers");
            }
            retained->idle_spawn_rate = 1;
        }
        else {
            if (free_length > retained->idle_spawn_rate) {
                free_length = retained->idle_spawn_rate;
            }
            if (retained->idle_spawn_rate >= 8) {
                ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00486)
                             "server seems busy, (you may need "
                             "to increase StartServers, ThreadsPerChild "
                             "or Min/MaxSpareThreads), "
                             "spawning %d children, there are around %d idle "
                             "threads, and %d total children", free_length,
                             idle_thread_count, total_non_dead);
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