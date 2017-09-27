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
    ++my_generation;
    ap_scoreboard_image->global->running_generation = my_generation;

    if (is_graceful) {
        ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, ap_server_conf,
                    "Graceful restart requested, doing restart");

        /* kill off the idle ones */
        ap_mpm_pod_killpg(pod, max_daemons_limit);

        /* This is mostly for debugging... so that we know what is still
         * gracefully dealing with existing request.  This will break
         * in a very nasty way if we ever have the scoreboard totally
         * file-based (no shared memory)
         */
