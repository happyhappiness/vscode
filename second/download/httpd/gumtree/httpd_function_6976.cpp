static apr_status_t hc_check_http(baton_t *baton)
{
    int status;
    proxy_conn_rec *backend = NULL;
    sctx_t *ctx = baton->ctx;
    proxy_worker *hc = baton->hc;
    proxy_worker *worker = baton->worker;
    apr_pool_t *ptemp = baton->ptemp;
    request_rec *r;
    wctx_t *wctx;
    hc_condition_t *cond;
    apr_bucket_brigade *bb;

    wctx = (wctx_t *)hc->context;
    if (!wctx->req || !wctx->method) {
        return APR_ENOTIMPL;
    }

    if ((status = hc_get_backend("HCOH", &backend, hc, ctx, ptemp)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }
    if ((status = ap_proxy_connect_backend("HCOH", backend, hc, ctx->s)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }

    if (!backend->connection) {
        if ((status = ap_proxy_connection_create("HCOH", backend, NULL, ctx->s)) != OK) {
            return backend_cleanup("HCOH", backend, ctx->s, status);
        }
    }

    r = create_request_rec(ptemp, backend->connection, wctx->method);
    bb = apr_brigade_create(r->pool, r->connection->bucket_alloc);

    if ((status = hc_send(r, wctx->req, bb)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }
    if ((status = hc_read_headers(r)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }
    if (!r->header_only) {
        apr_table_t *saved_headers_in = r->headers_in;
        r->headers_in = apr_table_copy(r->pool, r->headers_out);
        ap_proxy_pre_http_request(backend->connection, r);
        status = hc_read_body(r, bb);
        r->headers_in = saved_headers_in;
        if (status != OK) {
            return backend_cleanup("HCOH", backend, ctx->s, status);
        }
        r->trailers_out = apr_table_copy(r->pool, r->trailers_in);
    }

    if (*worker->s->hcexpr &&
            (cond = (hc_condition_t *)apr_table_get(ctx->conditions, worker->s->hcexpr)) != NULL) {
        const char *err;
        int ok = ap_expr_exec(r, cond->pexpr, &err);
        if (ok > 0) {
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                         "Condition %s for %s (%s): passed", worker->s->hcexpr,
                         hc->s->name, worker->s->name);
        } else if (ok < 0 || err) {
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, ctx->s, APLOGNO(03301)
                         "Error on checking condition %s for %s (%s): %s", worker->s->hcexpr,
                         hc->s->name, worker->s->name, err);
            status = !OK;
        } else {
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                         "Condition %s for %s (%s) : failed", worker->s->hcexpr,
                         hc->s->name, worker->s->name);
            status = !OK;
        }
    } else if (r->status < 200 || r->status > 399) {
        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                     "Response status %i for %s (%s): failed", r->status,
                     hc->s->name, worker->s->name);
        status = !OK;
    }
    return backend_cleanup("HCOH", backend, ctx->s, status);
}