                 (!ap_graceful_shutdown_timeout || apr_time_now() < cutoff));

        /* We might be here because we received SIGTERM, either
         * way, try and make sure that all of our processes are
         * really dead.
         */
        ap_worker_pod_killpg(pod, ap_daemons_limit, FALSE);
        ap_reclaim_child_processes(1);

        return DONE;
    }

    /* we've been told to restart */
    apr_signal(SIGHUP, SIG_IGN);

    if (one_process) {
        /* not worth thinking about */
        return DONE;
    }

    /* advance to the next generation */
    /* XXX: we really need to make sure this new generation number isn't in
     * use by any of the children.
     */
    ++my_generation;
    ap_scoreboard_image->global->running_generation = my_generation;

    if (is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");
        /* wake up the children...time to die.  But we'll have more soon */
        ap_worker_pod_killpg(pod, ap_daemons_limit, TRUE);


        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.
         */

    }
    else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
        ap_worker_pod_killpg(pod, ap_daemons_limit, FALSE);

        ap_reclaim_child_processes(1);                /* Start with SIGTERM */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                    "SIGHUP received.  Attempting to restart");
    }

    return OK;
}

/* This really should be a post_config hook, but the error log is already
 * redirected by that point, so we need to do this in the open_logs phase.
 */
static int worker_open_logs(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    int startup = 0;
    int level_flags = 0;
    apr_status_t rv;

    pconf = p;

    /* the reverse of pre_config, we want this only the first time around */
    if (retained->module_loads == 1) {
        startup = 1;
        level_flags |= APLOG_STARTUP;
    }

    if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT | level_flags, 0,
                     (startup ? NULL : s),
                     "no listening sockets available, shutting down");
        return DONE;
    }

    if (!one_process) {
        if ((rv = ap_worker_pod_open(pconf, &pod))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT | level_flags, rv,
                         (startup ? NULL : s),
                         "could not open pipe-of-death");
            return DONE;
        }
    }
    return OK;
}

static int worker_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp)
{
    int no_detach, debug, foreground;
    apr_status_t rv;
    const char *userdata_key = "mpm_worker_module";

    mpm_state = AP_MPMQ_STARTING;

    debug = ap_exists_config_define("DEBUG");

    if (debug) {
        foreground = one_process = 1;
        no_detach = 0;
    }
    else {
        one_process = ap_exists_config_define("ONE_PROCESS");
        no_detach = ap_exists_config_define("NO_DETACH");
        foreground = ap_exists_config_define("FOREGROUND");
    }

    ap_mutex_register(pconf, AP_ACCEPT_MUTEX_TYPE, NULL, APR_LOCK_DEFAULT, 0);

    /* sigh, want this only the second time around */
    retained = ap_retained_data_get(userdata_key);
    if (!retained) {
        retained = ap_retained_data_create(userdata_key, sizeof(*retained));
    }
    ++retained->module_loads;
    if (retained->module_loads == 2) {
        is_graceful = 0;

        if (!one_process && !foreground) {
            rv = apr_proc_detach(no_detach ? APR_PROC_DETACH_FOREGROUND
                                           : APR_PROC_DETACH_DAEMONIZE);
            if (rv != APR_SUCCESS) {
