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

static void server_main_loop(int remaining_children_to_start)
{
    ap_generation_t old_gen;
    int child_slot;
    apr_exit_why_e exitwhy;
    int status, processed_status;
    apr_proc_t pid;
    int i;

    while (!restart_pending && !shutdown_pending) {
        ap_wait_or_timeout(&exitwhy, &status, &pid, pconf, ap_server_conf);

        if (pid.pid != -1) {
            processed_status = ap_process_child_status(&pid, exitwhy, status);
            child_slot = ap_find_child_by_pid(&pid);
            if (processed_status == APEXIT_CHILDFATAL) {
                /* fix race condition found in PR 39311
                 * A child created at the same time as a graceful happens 
                 * can find the lock missing and create a fatal error.
                 * It is not fatal for the last generation to be in this state.
                 */
                if (child_slot < 0
                    || ap_get_scoreboard_process(child_slot)->generation
                       == retained->my_generation) {
                    shutdown_pending = 1;
                    child_fatal = 1;
                    return;
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(00487)
                                 "Ignoring fatal error in child of previous "
                                 "generation (pid %ld).",
                                 (long)pid.pid);
                    retained->sick_child_detected = 1;
                }
            }
            else if (processed_status == APEXIT_CHILDSICK) {
                /* tell perform_idle_server_maintenance to check into this
                 * on the next timer pop
                 */
                retained->sick_child_detected = 1;
            }
            /* non-fatal death... note that it's gone in the scoreboard. */
            if (child_slot >= 0) {
                for (i = 0; i < threads_per_child; i++)
                    ap_update_child_status_from_indexes(child_slot, i,
                                                        SERVER_DEAD,
                                                        (request_rec *) NULL);

                event_note_child_killed(child_slot, 0, 0);
                ap_scoreboard_image->parent[child_slot].quiescing = 0;
                if (processed_status == APEXIT_CHILDSICK) {
                    /* resource shortage, minimize the fork rate */
                    retained->idle_spawn_rate = 1;
                }
                else if (remaining_children_to_start
                         && child_slot < ap_daemons_limit) {
                    /* we're still doing a 1-for-1 replacement of dead
                     * children with new children
                     */
                    make_child(ap_server_conf, child_slot);
                    --remaining_children_to_start;
                }
            }
            else if (ap_unregister_extra_mpm_process(pid.pid, &old_gen) == 1) {

                event_note_child_killed(-1, /* already out of the scoreboard */
                                        pid.pid, old_gen);
#if APR_HAS_OTHER_CHILD
            }
            else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH,
                                                status) == 0) {
                /* handled */
#endif
            }
            else if (retained->is_graceful) {
                /* Great, we've probably just lost a slot in the
                 * scoreboard.  Somehow we don't know about this child.
                 */
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0,
                             ap_server_conf, APLOGNO(00488)
                             "long lost child came home! (pid %ld)",
                             (long) pid.pid);
            }
            /* Don't perform idle maintenance when a child dies,
             * only do it when there's a timeout.  Remember only a
             * finite number of children can die, and it's pretty
