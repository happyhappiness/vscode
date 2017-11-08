static void server_main_loop(int remaining_children_to_start)
{
    int child_slot;
    apr_exit_why_e exitwhy;
    int status;
    apr_proc_t pid;
    int i;

    while (!restart_pending && !shutdown_pending) {
        ap_wait_or_timeout(&exitwhy, &status, &pid, pconf);
        
        if (pid.pid != -1) {
            if (ap_process_child_status(&pid, exitwhy, status)
                == APEXIT_CHILDFATAL) {
                shutdown_pending = 1;
                child_fatal = 1;
                return;
            }
            /* non-fatal death... note that it's gone in the child table and
             * clean out the status table. */
            child_slot = -1;
            for (i = 0; i < ap_max_daemons_limit; ++i) {
                if (ap_child_table[i].pid == pid.pid) {
                    child_slot = i;
                    break;
                }
            }
            if (child_slot >= 0) {
                ap_child_table[child_slot].pid = 0;
                ap_update_child_status_from_indexes(child_slot, i, SERVER_DEAD,
                                                    (request_rec *) NULL);

                
                if (remaining_children_to_start
                    && child_slot < num_daemons) {
                    /* we're still doing a 1-for-1 replacement of dead
                     * children with new children
                     */
                    make_child(ap_server_conf, child_slot);
                    --remaining_children_to_start;
                }
#if APR_HAS_OTHER_CHILD
            }
            else if (apr_proc_other_child_read(&pid, status) == 0) {
            /* handled */
#endif
            }
            else if (is_graceful) {
                /* Great, we've probably just lost a slot in the
                * child table.  Somehow we don't know about this
                * child.
                */
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, 
                             ap_server_conf,
                             "long lost child came home! (pid %ld)", 
                             (long)pid.pid);
            }
            /* Don't perform idle maintenance when a child dies,
             * only do it when there's a timeout.  Remember only a
             * finite number of children can die, and it's pretty
             * pathological for a lot to die suddenly.
             */
            continue;
        }
        else if (remaining_children_to_start) {
            /* we hit a 1 second timeout in which none of the previous
             * generation of children needed to be reaped... so assume
             * they're all done, and pick up the slack if any is left.
             */
            remaining_children_to_start = \
                startup_children(remaining_children_to_start);
            /* In any event we really shouldn't do the code below because
             * few of the servers we just started are in the IDLE state
             * yet, so we'd mistakenly create an extra server.
             */
            continue;
        }

        perform_child_maintenance();
    }
}