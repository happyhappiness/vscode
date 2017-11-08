static apr_status_t reqtimeout_filter(ap_filter_t *f,
                                      apr_bucket_brigade *bb,
                                      ap_input_mode_t mode,
                                      apr_read_type_e block,
                                      apr_off_t readbytes)
{
    reqtimeout_ctx *ctx;
    apr_time_t time_left;
    apr_time_t now;
    apr_status_t rv;
    apr_interval_time_t saved_sock_timeout = -1;
    reqtimeout_con_cfg *ccfg;

    ctx = f->ctx;
    AP_DEBUG_ASSERT(ctx != NULL);

    ccfg = ap_get_module_config(f->c->conn_config, &reqtimeout_module);
    AP_DEBUG_ASSERT(ccfg != NULL);

    if (ccfg->in_keep_alive) {
        /* For this read, the normal keep-alive timeout must be used */
        ccfg->in_keep_alive = 0;
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    now = apr_time_now();
    if (ccfg->new_timeout > 0) {
        /* set new timeout */
        ccfg->timeout_at = now + apr_time_from_sec(ccfg->new_timeout);
        ccfg->new_timeout = 0;
        if (ccfg->new_max_timeout > 0) {
            ccfg->max_timeout_at = now + apr_time_from_sec(ccfg->new_max_timeout);
            ccfg->new_max_timeout = 0;
        }
    }
    else if (ccfg->timeout_at == 0) {
        /* no timeout set */
        return ap_get_brigade(f->next, bb, mode, block, readbytes);
    }

    time_left = ccfg->timeout_at - now;
    if (time_left <= 0) {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                      "Request %s read timeout", ccfg->type);
        return APR_TIMEUP;
    }

    if (block == APR_NONBLOCK_READ || mode == AP_MODE_INIT
        || mode == AP_MODE_EATCRLF) {
        rv = ap_get_brigade(f->next, bb, mode, block, readbytes);
        if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
            extend_timeout(ccfg, bb);
        }
        return rv;
    }

    if (time_left < apr_time_from_sec(1)) {
        time_left = apr_time_from_sec(1);
    }

    rv = apr_socket_timeout_get(ctx->socket, &saved_sock_timeout);
    AP_DEBUG_ASSERT(rv == APR_SUCCESS);

    if (saved_sock_timeout >= time_left) {
        rv = apr_socket_timeout_set(ctx->socket, time_left);
        AP_DEBUG_ASSERT(rv == APR_SUCCESS);
    }
    else {
        saved_sock_timeout = -1;
    }

    rv = ap_get_brigade(f->next, bb, mode, block, readbytes);

    if (saved_sock_timeout != -1) {
        apr_socket_timeout_set(ctx->socket, saved_sock_timeout);
    }

    if (ccfg->min_rate > 0 && rv == APR_SUCCESS) {
        extend_timeout(ccfg, bb);
    }

    if (APR_STATUS_IS_TIMEUP(rv)) {
        ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, f->c,
                      "Request %s read timeout", ccfg->type);
    }
    return rv;
}