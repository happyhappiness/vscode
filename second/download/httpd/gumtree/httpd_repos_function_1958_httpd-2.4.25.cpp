static int hc_determine_connection(sctx_t *ctx, proxy_worker *worker) {
    apr_status_t rv = APR_SUCCESS;
    int will_reuse = worker->s->is_address_reusable && !worker->s->disablereuse;
    /*
     * normally, this is done in ap_proxy_determine_connection().
     * TODO: Look at using ap_proxy_determine_connection() with a
     * fake request_rec
     */
    if (!worker->cp->addr || !will_reuse) {
        rv = apr_sockaddr_info_get(&(worker->cp->addr), worker->s->hostname, APR_UNSPEC,
                                   worker->s->port, 0, ctx->p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03249)
                         "DNS lookup failure for: %s:%d",
                         worker->s->hostname, (int)worker->s->port);
        }
    }
    return (rv == APR_SUCCESS ? OK : !OK);
}