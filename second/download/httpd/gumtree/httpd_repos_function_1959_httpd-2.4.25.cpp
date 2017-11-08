static apr_status_t hc_init_worker(sctx_t *ctx, proxy_worker *worker) {
    apr_status_t rv = APR_SUCCESS;
    /*
     * Since this is the watchdog, workers never actually handle a
     * request here, and so the local data isn't initialized (of
     * course, the shared memory is). So we need to bootstrap
     * worker->cp. Note, we only need do this once.
     */
    if (!worker->cp) {
        rv = ap_proxy_initialize_worker(worker, ctx->s, ctx->p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, rv, ctx->s, APLOGNO(03250) "Cannot init worker");
            return rv;
        }
        rv = (hc_determine_connection(ctx, worker) == OK ? APR_SUCCESS : APR_EGENERAL);
    }
    return rv;
}