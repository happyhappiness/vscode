	    child_slot = find_child_by_pid(&pid);
	    if (child_slot >= 0) {
		(void) ap_update_child_status_from_indexes(child_slot, 0, SERVER_DEAD,
                                                           (request_rec *) NULL);
                if (processed_status == APEXIT_CHILDSICK) {
                    /* child detected a resource shortage (E[NM]FILE, ENOBUFS, etc)
                     * cut the fork rate to the minimum
                     */
                    idle_spawn_rate = 1;
                }
                else if (remaining_children_to_start
		    && child_slot < ap_daemons_limit) {
		    /* we're still doing a 1-for-1 replacement of dead
                     * children with new children
                     */
		    make_child(ap_server_conf, child_slot);
		    --remaining_children_to_start;
		}
#if APR_HAS_OTHER_CHILD
	    }
            else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH, status) == APR_SUCCESS) {
		/* handled */
#endif
	    }
	    else if (is_graceful) {
		/* Great, we've probably just lost a slot in the
                 * scoreboard.  Somehow we don't know about this
                 * child.
                 */
                ap_log_error(APLOG_MARK, APLOG_WARNING,
                            0, ap_server_conf,
			    "long lost child came home! (pid %ld)", (long)pid.pid);
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
	    startup_children(remaining_children_to_start);
	    remaining_children_to_start = 0;
	    /* In any event we really shouldn't do the code below because
             * few of the servers we just started are in the IDLE state
             * yet, so we'd mistakenly create an extra server.
             */
	    continue;
	}

	perform_idle_server_maintenance(pconf);
#ifdef TPF
        shutdown_pending = os_check_server(tpf_server_name);
        ap_check_signals();
        sleep(1);
#endif /*TPF */
    }
    } /* one_process */

    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !is_graceful) {
        /* Time to shut down:
	 * Kill child processes, tell them to call child_exit, etc...
	 */
	if (unixd_killpg(getpgrp(), SIGTERM) < 0) {
	    ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, "killpg SIGTERM");
	}
	ap_reclaim_child_processes(1);		/* Start with SIGTERM */
