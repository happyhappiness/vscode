}

/*****************************************************************
 * Executive routines.
 */

int ap_mpm_run(apr_pool_t *_pconf, apr_pool_t *plog, server_rec *s)
{
    int index;
    int remaining_children_to_start;
    apr_status_t rv;

    ap_log_pid(pconf, ap_pid_fname);

    first_server_limit = server_limit;
    if (changed_limit_at_restart) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
                     "WARNING: Attempt to change ServerLimit "
                     "ignored during restart");
        changed_limit_at_restart = 0;
    }

    /* Initialize cross-process accept lock */
    ap_lock_fname = apr_psprintf(_pconf, "%s.%" APR_PID_T_FMT,
                                 ap_server_root_relative(_pconf, ap_lock_fname),
                                 ap_my_pid);

    rv = apr_proc_mutex_create(&accept_mutex, ap_lock_fname,
                               ap_accept_lock_mech, _pconf);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create accept lock (%s) (%d)",
                     ap_lock_fname, ap_accept_lock_mech);
        mpm_state = AP_MPMQ_STOPPING;
        return 1;
    }

#if APR_USE_SYSVSEM_SERIALIZE
    if (ap_accept_lock_mech == APR_LOCK_DEFAULT ||
        ap_accept_lock_mech == APR_LOCK_SYSVSEM) {
#else
    if (ap_accept_lock_mech == APR_LOCK_SYSVSEM) {
#endif
        rv = unixd_set_proc_mutex_perms(accept_mutex);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                         "Couldn't set permissions on cross-process lock; "
                         "check User and Group directives");
            mpm_state = AP_MPMQ_STOPPING;
            return 1;
        }
    }

    if (!is_graceful) {
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            mpm_state = AP_MPMQ_STOPPING;
            return 1;
        }
        /* fix the generation number in the global score; we just got a new,
         * cleared scoreboard
         */
        ap_scoreboard_image->global->running_generation = ap_my_generation;
    }

    set_signals();

    if (one_process) {
        AP_MONCONTROL(1);
