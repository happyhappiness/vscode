                 (!ap_graceful_shutdown_timeout || apr_time_now() < cutoff));

        /* We might be here because we received SIGTERM, either
         * way, try and make sure that all of our processes are
         * really dead.
         */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, FALSE);
        ap_reclaim_child_processes(1);

        return 1;
    }

    /* we've been told to restart */
    apr_signal(SIGHUP, SIG_IGN);

    if (one_process) {
        /* not worth thinking about */
        return 1;
    }

    /* advance to the next generation */
    /* XXX: we really need to make sure this new generation number isn't in
     * use by any of the children.
     */
    ++ap_my_generation;
    ap_scoreboard_image->global->running_generation = ap_my_generation;

    if (is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                     AP_SIG_GRACEFUL_STRING " received.  Doing graceful restart");
        /* wake up the children...time to die.  But we'll have more soon */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, TRUE);


        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.
         */

    }
    else {
        /* Kill 'em all.  Since the child acts the same on the parents SIGTERM
         * and a SIGHUP, we may as well use the same signal, because some user
         * pthreads are stealing signals from us left and right.
         */
        ap_mpm_pod_killpg(pod, ap_daemons_limit, FALSE);

        ap_reclaim_child_processes(1);                /* Start with SIGTERM */
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                    "SIGHUP received.  Attempting to restart");
    }

    return 0;
}

/* This really should be a post_config hook, but the error log is already
 * redirected by that point, so we need to do this in the open_logs phase.
 */
static int worker_open_logs(apr_pool_t *p, apr_pool_t *plog, apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;

    pconf = p;
    ap_server_conf = s;

    if ((num_listensocks = ap_setup_listeners(ap_server_conf)) < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT|APLOG_STARTUP, 0,
                     NULL, "no listening sockets available, shutting down");
        return DONE;
    }

    if (!one_process) {
        if ((rv = ap_mpm_pod_open(pconf, &pod))) {
            ap_log_error(APLOG_MARK, APLOG_CRIT|APLOG_STARTUP, rv, NULL,
                    "Could not open pipe-of-death.");
            return DONE;
        }
    }
    return OK;
}

static int worker_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp)
{
    static int restart_num = 0;
    int no_detach, debug, foreground;
    ap_directive_t *pdir;
    ap_directive_t *max_clients = NULL;
    apr_status_t rv;

    mpm_state = AP_MPMQ_STARTING;

    /* make sure that "ThreadsPerChild" gets set before "MaxClients" */
    for (pdir = ap_conftree; pdir != NULL; pdir = pdir->next) {
        if (strncasecmp(pdir->directive, "ThreadsPerChild", 15) == 0) {
            if (!max_clients) {
                break; /* we're in the clear, got ThreadsPerChild first */
            }
            else {
                /* now to swap the data */
                ap_directive_t temp;

                temp.directive = pdir->directive;
                temp.args = pdir->args;
                /* Make sure you don't change 'next', or you may get loops! */
                /* XXX: first_child, parent, and data can never be set
                 * for these directives, right? -aaron */
                temp.filename = pdir->filename;
                temp.line_num = pdir->line_num;

                pdir->directive = max_clients->directive;
                pdir->args = max_clients->args;
                pdir->filename = max_clients->filename;
                pdir->line_num = max_clients->line_num;

                max_clients->directive = temp.directive;
                max_clients->args = temp.args;
                max_clients->filename = temp.filename;
                max_clients->line_num = temp.line_num;
                break;
            }
        }
        else if (!max_clients
                 && strncasecmp(pdir->directive, "MaxClients", 10) == 0) {
            max_clients = pdir;
        }
    }

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

    /* sigh, want this only the second time around */
    if (restart_num++ == 1) {
        is_graceful = 0;

        if (!one_process && !foreground) {
            rv = apr_proc_detach(no_detach ? APR_PROC_DETACH_FOREGROUND
                                           : APR_PROC_DETACH_DAEMONIZE);
            if (rv != APR_SUCCESS) {
