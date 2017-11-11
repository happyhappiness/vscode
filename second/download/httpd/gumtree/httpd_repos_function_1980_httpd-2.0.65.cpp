static int net_time_filter(ap_filter_t *f, apr_bucket_brigade *b,
                           ap_input_mode_t mode, apr_read_type_e block,
                           apr_off_t readbytes)
{
    net_time_filter_ctx_t *ctx = f->ctx;
    int keptalive = f->c->keepalive == AP_CONN_KEEPALIVE;

    if (!ctx) {
        f->ctx = ctx = apr_palloc(f->r->pool, sizeof(*ctx));
        ctx->first_line = 1;
        ctx->csd = ap_get_module_config(f->c->conn_config, &core_module);        
    }

    if (mode != AP_MODE_INIT && mode != AP_MODE_EATCRLF) {
        if (keptalive && ctx->first_line) {
            apr_socket_timeout_set(ctx->csd,
                                   f->c->base_server->keep_alive_timeout);
            ctx->first_line = 0;
        }
        else {
            if (keptalive) {
                apr_socket_timeout_set(ctx->csd, f->c->base_server->timeout);
            }
        }
    }
    return ap_get_brigade(f->next, b, mode, block, readbytes);
}