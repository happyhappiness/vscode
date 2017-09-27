        hc->s->method = worker->s->method;
        rv = apr_uri_parse(p, url, &uri);
        if (rv == APR_SUCCESS) {
            wctx->path = apr_pstrdup(ctx->p, uri.path);
        }
        wctx->w = worker;
        create_hcheck_req(wctx, hc, ctx->p);
        hc->context = wctx;
        apr_hash_set(ctx->hcworkers, &worker, sizeof worker, hc);
    }
    /* This *could* have changed via the Balancer Manager */
    /* TODO */
    if (hc->s->method != worker->s->method) {
        wctx_t *wctx = hc->context;
        port = (worker->s->port ? worker->s->port
                                : ap_proxy_port_of_scheme(worker->s->scheme));
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03311)
                     "Updating hc worker %pp for %s://%s:%d",
                     worker, worker->s->scheme, worker->s->hostname,
                     (int)port);
        hc->s->method = worker->s->method;
        create_hcheck_req(wctx, hc, ctx->p);
    }
    return hc;
}

static int hc_determine_connection(sctx_t *ctx, proxy_worker *worker,
                                   apr_sockaddr_t **addr, apr_pool_t *p)
{
    apr_status_t rv = APR_SUCCESS;
    /*
     * normally, this is done in ap_proxy_determine_connection().
     * TODO: Look at using ap_proxy_determine_connection() with a
     * fake request_rec
     */
    if (worker->cp->addr) {
        *addr = worker->cp->addr;
    }
    else {
        rv = apr_sockaddr_info_get(addr, worker->s->hostname,
                                   APR_UNSPEC, worker->s->port, 0, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03249)
                         "DNS lookup failure for: %s:%d",
                         worker->s->hostname, (int)worker->s->port);
        }
    }
    return (rv == APR_SUCCESS ? OK : !OK);
}

static apr_status_t hc_init_worker(sctx_t *ctx, proxy_worker *worker)
{
    apr_status_t rv = APR_SUCCESS;
    /*
     * Since this is the watchdog, workers never actually handle a
     * request here, and so the local data isn't initialized (of
     * course, the shared memory is). So we need to bootstrap
     * worker->cp. Note, we only need do this once.
