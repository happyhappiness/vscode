}

/*****************************************************************
 * Executive routines.
 */

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

    if (one_process) {
        AP_MONCONTROL(1);
