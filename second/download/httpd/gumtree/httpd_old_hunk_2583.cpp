
    switch (state) {
        case AP_WATCHDOG_STATE_STARTING:
            rv = hm_listen(ctx);
            if (rv) {
                ctx->status = rv;
                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, ctx->s,
                             "Heartmonitor: Unable to listen for connections!");
            }
            else {
                ctx->keep_running = 1;
                ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s,
                             "Heartmonitor: %s listener started.",
                             HM_WATHCHDOG_NAME);
            }
        break;
        case AP_WATCHDOG_STATE_RUNNING:
            /* store in the slotmem or in the file depending on configuration */
            hm_update_stats(ctx, pool);
