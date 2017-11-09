static apr_status_t hc_check_tcp(baton_t *baton)
{
    int status;
    sctx_t *ctx = baton->ctx;
    proxy_worker *hc = baton->hc;
    proxy_conn_rec *backend = NULL;

    status = hc_get_backend("HCTCP", &backend, hc, ctx, baton->ptemp);
    if (status == OK) {
        backend->addr = hc->cp->addr;
        status = ap_proxy_connect_backend("HCTCP", backend, hc, ctx->s);
        /* does an unconditional ap_proxy_is_socket_connected() */
    }
    return backend_cleanup("HCTCP", backend, ctx->s, status);
}