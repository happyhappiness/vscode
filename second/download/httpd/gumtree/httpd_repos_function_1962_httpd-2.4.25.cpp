static apr_status_t hc_check_tcp(sctx_t *ctx, apr_pool_t *ptemp, proxy_worker *worker)
{
    int status;
    proxy_conn_rec *backend = NULL;
    proxy_worker *hc;

    hc = hc_get_hcworker(ctx, worker, ptemp);

    status = hc_get_backend("HCTCP", &backend, hc, ctx);
    if (status == OK) {
        backend->addr = hc->cp->addr;
        status = ap_proxy_connect_backend("HCTCP", backend, hc, ctx->s);
        /* does an unconditional ap_proxy_is_socket_connected() */
    }
    return backend_cleanup("HCTCP", backend, ctx->s, status);
}