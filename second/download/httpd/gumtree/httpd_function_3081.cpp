static apr_status_t hm_watchdog_callback(int state, void *data,
                                         apr_pool_t *pool)
{
    apr_status_t rv = APR_SUCCESS;
    apr_time_t cur, now;
    hm_ctx_t *ctx = (hm_ctx_t *)data;

    if (!ctx->active) {
        return rv;
    }

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
            cur = now = apr_time_sec(apr_time_now());
            /* TODO: Insted HN_UPDATE_SEC use
             * the ctx->interval
             */
            while ((now - cur) < apr_time_sec(ctx->interval)) {
                int n;
                apr_status_t rc;
                apr_pool_t *p;
                apr_pollfd_t pfd;
                apr_interval_time_t timeout;

                apr_pool_create(&p, pool);

                pfd.desc_type = APR_POLL_SOCKET;
                pfd.desc.s = ctx->sock;
                pfd.p = p;
                pfd.reqevents = APR_POLLIN;

                timeout = apr_time_from_sec(1);

                rc = apr_poll(&pfd, 1, &n, timeout);

                if (!ctx->keep_running) {
                    apr_pool_destroy(p);
                    break;
                }
                if (rc == APR_SUCCESS && (pfd.rtnevents & APR_POLLIN)) {
                    hm_recv(ctx, p);
                }
                now = apr_time_sec(apr_time_now());
                apr_pool_destroy(p);
            }
        break;
        case AP_WATCHDOG_STATE_STOPPING:
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s,
                         "Heartmonitor: stopping %s listener.",
                         HM_WATHCHDOG_NAME);

            ctx->keep_running = 0;
            if (ctx->sock) {
                apr_socket_close(ctx->sock);
                ctx->sock = NULL;
            }
        break;
    }
    return rv;
}