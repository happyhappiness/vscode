        }

        perform_idle_server_maintenance();
    }
}

static int worker_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
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

    if (!is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            mpm_state = AP_MPMQ_STOPPING;
            return DONE;
        }
        /* fix the generation number in the global score; we just got a new,
         * cleared scoreboard
         */
        ap_scoreboard_image->global->running_generation = my_generation;
    }

    set_signals();
    /* Don't thrash... */
    if (max_spare_threads < min_spare_threads + threads_per_child)
        max_spare_threads = min_spare_threads + threads_per_child;

    /* If we're doing a graceful_restart then we're going to see a lot
     * of children exiting immediately when we get into the main loop
     * below (because we just sent them AP_SIG_GRACEFUL).  This happens pretty
     * rapidly... and for each one that exits we may start a new one, until
     * there are at least min_spare_threads idle threads, counting across
     * all children.  But we may be permitted to start more children than
     * that, so we'll just keep track of how many we're
     * supposed to start up without the 1 second penalty between each fork.
     */
    remaining_children_to_start = ap_daemons_to_start;
    if (remaining_children_to_start > ap_daemons_limit) {
        remaining_children_to_start = ap_daemons_limit;
    }
