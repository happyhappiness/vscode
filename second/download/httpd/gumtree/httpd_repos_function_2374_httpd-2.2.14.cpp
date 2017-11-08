static void server_main_loop(int remaining_threads_to_start)
{
    int child_slot;
    apr_exit_why_e exitwhy;
    int status;
    apr_proc_t pid;
    int i;

    while (!restart_pending && !shutdown_pending) {

        ap_wait_or_timeout(&exitwhy, &status, &pid, pconf);

        if (pid.pid >= 0) {
            if (ap_process_child_status(&pid, exitwhy, status) == APEXIT_CHILDFATAL) {
                shutdown_pending = 1;
                child_fatal = 1;
                return;
            }
            /* non-fatal death... note that it's gone in the scoreboard. */
            child_slot = -1;
            for (i = 0; i < ap_max_child_assigned; ++i) {
                if (ap_scoreboard_image->servers[0][i].tid == pid.pid) {
                    child_slot = i;
                    break;
                }
            }
            if (child_slot >= 0) {
                ap_scoreboard_image->servers[0][child_slot].tid = 0;
                (void) ap_update_child_status_from_indexes(0, child_slot,
                                                           SERVER_DEAD,
                                                           (request_rec*)NULL);

                if (remaining_threads_to_start
                            && child_slot < ap_thread_limit) {
                    /* we're still doing a 1-for-1 replacement of dead
                     * children with new children
                     */
                    make_worker(child_slot);
                    --remaining_threads_to_start;
                        }
/* TODO
#if APR_HAS_OTHER_CHILD
            }
            else if (apr_proc_other_child_refresh(&pid, status) == 0) {
#endif
*/
            }
            else if (is_graceful) {
                /* Great, we've probably just lost a slot in the
                 * scoreboard.  Somehow we don't know about this
                 * child.
                 */
                 ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf,
                                          "long lost child came home! (pid %ld)", pid.pid);
            }

            /* Don't perform idle maintenance when a child dies,
             * only do it when there's a timeout.  Remember only a
             * finite number of children can die, and it's pretty
             * pathological for a lot to die suddenly.
             */
             continue;
         }
             else if (remaining_threads_to_start) {
             /* we hit a 1 second timeout in which none of the previous
              * generation of children needed to be reaped... so assume
              * they're all done, and pick up the slack if any is left.
              */
              startup_threads(remaining_threads_to_start);
              remaining_threads_to_start = 0;
              /* In any event we really shouldn't do the code below because
               * few of the servers we just started are in the IDLE state
               * yet, so we'd mistakenly create an extra server.
               */
              continue;
         }
         perform_idle_server_maintenance();
    }
}