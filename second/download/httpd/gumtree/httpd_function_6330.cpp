static proxy_worker *hc_get_hcworker(sctx_t *ctx, proxy_worker *worker,
                                     apr_pool_t *p)
{
    proxy_worker *hc = NULL;
    const char* wptr;
    apr_port_t port;

    wptr = apr_psprintf(ctx->p, "%pp", worker);
    hc = (proxy_worker *)apr_hash_get(ctx->hcworkers, wptr, APR_HASH_KEY_STRING);
    port = (worker->s->port ? worker->s->port : ap_proxy_port_of_scheme(worker->s->scheme));
    if (!hc) {
        apr_uri_t uri;
        apr_status_t rv;
        const char *url = worker->s->name;
        wctx_t *wctx = apr_pcalloc(ctx->p, sizeof(wctx_t));

        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03248)
                     "Creating hc worker %s for %s://%s:%d",
                     wptr, worker->s->scheme, worker->s->hostname,
                     (int)port);

        ap_proxy_define_worker(ctx->p, &hc, NULL, NULL, worker->s->name, 0);
        PROXY_STRNCPY(hc->s->name,     wptr);
        PROXY_STRNCPY(hc->s->hostname, worker->s->hostname);
        PROXY_STRNCPY(hc->s->scheme,   worker->s->scheme);
        PROXY_STRNCPY(hc->s->hcuri,    worker->s->hcuri);
        PROXY_STRNCPY(hc->s->hcexpr,   worker->s->hcexpr);
        hc->hash.def = hc->s->hash.def = ap_proxy_hashfunc(hc->s->name, PROXY_HASHFUNC_DEFAULT);
        hc->hash.fnv = hc->s->hash.fnv = ap_proxy_hashfunc(hc->s->name, PROXY_HASHFUNC_FNV);
        hc->s->port = port;
        /* Do not disable worker in case of errors */
        hc->s->status |= PROXY_WORKER_IGNORE_ERRORS;
        /* Mark as the "generic" worker */
        hc->s->status |= PROXY_WORKER_GENERIC;
        ap_proxy_initialize_worker(hc, ctx->s, ctx->p);
        hc->s->is_address_reusable = worker->s->is_address_reusable;
        hc->s->disablereuse = worker->s->disablereuse;
        hc->s->method = worker->s->method;
        rv = apr_uri_parse(p, url, &uri);
        if (rv == APR_SUCCESS) {
            wctx->path = apr_pstrdup(ctx->p, uri.path);
        }
        wctx->w = worker;
        hc->context = wctx;
        apr_hash_set(ctx->hcworkers, wptr, APR_HASH_KEY_STRING, hc);
    }
    /* This *could* have changed via the Balancer Manager */
    /* TODO */
    if (hc->s->method != worker->s->method) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03311)
                     "Updating hc worker %s for %s://%s:%d",
                     wptr, worker->s->scheme, worker->s->hostname,
                     (int)port);
        hc->s->method = worker->s->method;
        apr_hash_set(ctx->hcworkers, wptr, APR_HASH_KEY_STRING, hc);
    }
    return hc;
}