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

static int reqtimeout_pre_conn(conn_rec *c, void *csd)
{
    reqtimeout_ctx *ctx;
    reqtimeout_con_cfg *ccfg;
    reqtimeout_srv_cfg *cfg;

    cfg = ap_get_module_config(c->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);
    if (cfg->header_timeout <= 0 && cfg->body_timeout <= 0) {
        /* not configured for this vhost */
        return OK;
    }

    ctx = apr_pcalloc(c->pool, sizeof(reqtimeout_ctx));
    ctx->socket = csd;

    ccfg = apr_pcalloc(c->pool, sizeof(reqtimeout_con_cfg));
    ccfg->new_timeout = cfg->header_timeout;
    ccfg->new_max_timeout = cfg->header_max_timeout;
    ccfg->type = "header";
    ccfg->min_rate = cfg->header_min_rate;
    ccfg->rate_factor = cfg->header_rate_factor;
    ap_set_module_config(c->conn_config, &reqtimeout_module, ccfg);

    ap_add_input_filter("reqtimeout", ctx, NULL, c);
    return OK;
}

static int reqtimeout_after_headers(request_rec *r)
{
    reqtimeout_srv_cfg *cfg;
    reqtimeout_con_cfg *ccfg =
        ap_get_module_config(r->connection->conn_config, &reqtimeout_module);

    if (ccfg == NULL) {
        /* not configured for this vhost */
        return OK;
    }

    cfg = ap_get_module_config(r->connection->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);

    ccfg->timeout_at = 0;
    ccfg->max_timeout_at = 0;
    ccfg->new_timeout = cfg->body_timeout;
    ccfg->new_max_timeout = cfg->body_max_timeout;
    ccfg->min_rate = cfg->body_min_rate;
    ccfg->rate_factor = cfg->body_rate_factor;
    ccfg->type = "body";

    return OK;
}

static int reqtimeout_after_body(request_rec *r)
{
    reqtimeout_srv_cfg *cfg;
    reqtimeout_con_cfg *ccfg =
        ap_get_module_config(r->connection->conn_config, &reqtimeout_module);

    if (ccfg == NULL) {
        /* not configured for this vhost */
        return OK;
    }

    cfg = ap_get_module_config(r->connection->base_server->module_config,
                               &reqtimeout_module);
    AP_DEBUG_ASSERT(cfg != NULL);
