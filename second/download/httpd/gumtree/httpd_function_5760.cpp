static int prefork_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    int index;
    int remaining_children_to_start;
    apr_status_t rv;

    ap_log_pid(pconf, ap_pid_fname);

    /* Initialize cross-process accept lock */
    rv = ap_proc_mutex_create(&accept_mutex, NULL, AP_ACCEPT_MUTEX_TYPE, NULL,
                              s, _pconf, 0);
    if (rv != APR_SUCCESS) {
        mpm_state = AP_MPMQ_STOPPING;
        return DONE;
    }

    if (!retained->is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            mpm_state = AP_MPMQ_STOPPING;
            return DONE;
        }
        /* fix the generation number in the global score; we just got a new,
         * cleared scoreboard
         */
        ap_scoreboard_image->global->running_generation = retained->my_generation;
    }

    restart_pending = shutdown_pending = 0;
    set_signals();

    if (one_process) {
        AP_MONCONTROL(1);
        make_child(ap_server_conf, 0);
        /* NOTREACHED */
    }
    else {
    if (ap_daemons_max_free < ap_daemons_min_free + 1)  /* Don't thrash... */
        ap_daemons_max_free = ap_daemons_min_free + 1;

    /* If we're doing a graceful_restart then we're going to see a lot
     * of children exiting immediately when we get into the main loop
     * below (because we just sent them AP_SIG_GRACEFUL).  This happens pretty
     * rapidly... and for each one that exits we'll start a new one until
     * we reach at least daemons_min_free.  But we may be permitted to
     * start more than that, so we'll just keep track of how many we're
     * supposed to start up without the 1 second penalty between each fork.
     */
    remaining_children_to_start = ap_daemons_to_start;
    if (remaining_children_to_start > ap_daemons_limit) {
        remaining_children_to_start = ap_daemons_limit;
    }
    if (!retained->is_graceful) {
        startup_children(remaining_children_to_start);
        remaining_children_to_start = 0;
    }
    else {
        /* give the system some time to recover before kicking into
         * exponential mode
         */
        retained->hold_off_on_exponential_spawning = 10;
    }

    ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00163)
                "%s configured -- resuming normal operations",
                ap_get_server_description());
    ap_log_error(APLOG_MARK, APLOG_INFO, 0, ap_server_conf, APLOGNO(00164)
                "Server built: %s", ap_get_server_built());
    ap_log_command_line(plog, s);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ap_server_conf, APLOGNO(00165)
                "Accept mutex: %s (default: %s)",
                apr_proc_mutex_name(accept_mutex),
                apr_proc_mutex_defname());

    mpm_state = AP_MPMQ_RUNNING;

    while (!restart_pending && !shutdown_pending) {
        int child_slot;
        apr_exit_why_e exitwhy;
        int status, processed_status;
        /* this is a memory leak, but I'll fix it later. */
        apr_proc_t pid;

        ap_wait_or_timeout(&exitwhy, &status, &pid, pconf, ap_server_conf);

        /* XXX: if it takes longer than 1 second for all our children
         * to start up and get into IDLE state then we may spawn an
         * extra child
         */
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
                    mpm_state = AP_MPMQ_STOPPING;
                    return DONE;
                }
                else {
                    ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(00166)
                                 "Ignoring fatal error in child of previous "
                                 "generation (pid %ld).",
                                 (long)pid.pid);
                }
            }

            /* non-fatal death... note that it's gone in the scoreboard. */
            if (child_slot >= 0) {
                (void) ap_update_child_status_from_indexes(child_slot, 0, SERVER_DEAD,
                                                           (request_rec *) NULL);
                prefork_note_child_killed(child_slot, 0, 0);
                if (processed_status == APEXIT_CHILDSICK) {
                    /* child detected a resource shortage (E[NM]FILE, ENOBUFS, etc)
                     * cut the fork rate to the minimum
                     */
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
#if APR_HAS_OTHER_CHILD
            }
            else if (apr_proc_other_child_alert(&pid, APR_OC_REASON_DEATH, status) == APR_SUCCESS) {
                /* handled */
#endif
            }
            else if (retained->is_graceful) {
                /* Great, we've probably just lost a slot in the
                 * scoreboard.  Somehow we don't know about this
                 * child.
                 */
                ap_log_error(APLOG_MARK, APLOG_WARNING,
                            0, ap_server_conf, APLOGNO(00167)
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
    }
    } /* one_process */

    mpm_state = AP_MPMQ_STOPPING;

    if (shutdown_pending && !retained->is_graceful) {
        /* Time to shut down:
         * Kill child processes, tell them to call child_exit, etc...
         */
        if (ap_unixd_killpg(getpgrp(), SIGTERM) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00168) "killpg SIGTERM");
        }
        ap_reclaim_child_processes(1, /* Start with SIGTERM */
                                   prefork_note_child_killed);

        /* cleanup pid file on normal shutdown */
        ap_remove_pid(pconf, ap_pid_fname);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00169)
                    "caught SIGTERM, shutting down");

        return DONE;
    } else if (shutdown_pending) {
        /* Time to perform a graceful shut down:
         * Reap the inactive children, and ask the active ones
         * to close their listeners, then wait until they are
         * all done to exit.
         */
        int active_children;
        apr_time_t cutoff = 0;

        /* Stop listening */
        ap_close_listeners();

        /* kill off the idle ones */
        ap_mpm_pod_killpg(pod, retained->max_daemons_limit);

        /* Send SIGUSR1 to the active children */
        active_children = 0;
        for (index = 0; index < ap_daemons_limit; ++index) {
            if (ap_scoreboard_image->servers[index][0].status != SERVER_DEAD) {
                /* Ask each child to close its listeners. */
                ap_mpm_safe_kill(MPM_CHILD_PID(index), AP_SIG_GRACEFUL);
                active_children++;
            }
        }

        /* Allow each child which actually finished to exit */
        ap_relieve_child_processes(prefork_note_child_killed);

        /* cleanup pid file */
        ap_remove_pid(pconf, ap_pid_fname);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00170)
           "caught " AP_SIG_GRACEFUL_STOP_STRING ", shutting down gracefully");

        if (ap_graceful_shutdown_timeout) {
            cutoff = apr_time_now() +
                     apr_time_from_sec(ap_graceful_shutdown_timeout);
        }

        /* Don't really exit until each child has finished */
        shutdown_pending = 0;
        do {
            /* Pause for a second */
            sleep(1);

            /* Relieve any children which have now exited */
            ap_relieve_child_processes(prefork_note_child_killed);

            active_children = 0;
            for (index = 0; index < ap_daemons_limit; ++index) {
                if (ap_mpm_safe_kill(MPM_CHILD_PID(index), 0) == APR_SUCCESS) {
                    active_children = 1;
                    /* Having just one child is enough to stay around */
                    break;
                }
            }
        } while (!shutdown_pending && active_children &&
                 (!ap_graceful_shutdown_timeout || apr_time_now() < cutoff));

        /* We might be here because we received SIGTERM, either
         * way, try and make sure that all of our processes are
         * really dead.
         */
        ap_unixd_killpg(getpgrp(), SIGTERM);

        return DONE;
    }

    /* we've been told to restart */
    apr_signal(SIGHUP, SIG_IGN);
    apr_signal(AP_SIG_GRACEFUL, SIG_IGN);
    if (one_process) {
        /* not worth thinking about */
        return DONE;
    }

    /* advance to the next generation */
    /* XXX: we really need to make sure this new generation number isn't in
     * use by any of the children.
     */
    ++retained->my_generation;
    ap_scoreboard_image->global->running_generation = retained->my_generation;

    if (retained->is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00171)
                    "Graceful restart requested, doing restart");

        /* kill off the idle ones */
        ap_mpm_pod_killpg(pod, retained->max_daemons_limit);

        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.  This will break
         * in a very nasty way if we ever have the scoreboard totally
         * file-based (no shared memory)
         */
        for (index = 0; index < ap_daemons_limit; ++index) {
            if (ap_scoreboard_image->servers[index][0].status != SERVER_DEAD) {
                ap_scoreboard_image->servers[index][0].status = SERVER_GRACEFUL;
                /* Ask each child to close its listeners.
                 *
                 * NOTE: we use the scoreboard, because if we send SIGUSR1
                 * to every process in the group, this may include CGI's,
                 * piped loggers, etc. They almost certainly won't handle
                 * it gracefully.
                 */
                ap_mpm_safe_kill(ap_scoreboard_image->parent[index].pid, AP_SIG_GRACEFUL);
            }
        }
    }
    else {
        /* Kill 'em off */
        if (ap_unixd_killpg(getpgrp(), SIGHUP) < 0) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, errno, ap_server_conf, APLOGNO(00172) "killpg SIGHUP");
        }
        ap_reclaim_child_processes(0, /* Not when just starting up */
                                   prefork_note_child_killed);
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf, APLOGNO(00173)
                    "SIGHUP received.  Attempting to restart");
    }

    return OK;
}