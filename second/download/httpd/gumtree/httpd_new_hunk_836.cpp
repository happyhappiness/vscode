           at a time so we need to fall on our sword... */
        ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
                     "Couldn't create accept lock");
        return 1;
    }

    /*
     * Startup/shutdown...
     */

    if (!is_graceful) {
        /* setup the scoreboard shared memory */
        if (ap_run_pre_mpm(s->process->pool, SB_SHARED) != OK) {
            return 1;
        }

