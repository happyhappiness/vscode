static apr_status_t hc_check_http(sctx_t *ctx, apr_pool_t *ptemp, proxy_worker *worker)
{
    int status;
    proxy_conn_rec *backend = NULL;
    proxy_worker *hc;
    conn_rec c;
    request_rec *r;
    wctx_t *wctx;
    hc_condition_t *cond;
    const char *method = NULL;

    hc = hc_get_hcworker(ctx, worker, ptemp);
    wctx = (wctx_t *)hc->context;

    if ((status = hc_get_backend("HCOH", &backend, hc, ctx)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }
    if ((status = ap_proxy_connect_backend("HCOH", backend, hc, ctx->s)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }

    if (!backend->connection) {
        if ((status = ap_proxy_connection_create("HCOH", backend, &c, ctx->s)) != OK) {
            return backend_cleanup("HCOH", backend, ctx->s, status);
        }
    }
    switch (hc->s->method) {
        case OPTIONS:
            if (!wctx->req) {
                wctx->req = apr_psprintf(ctx->p,
                                   "OPTIONS * HTTP/1.0\r\nHost: %s:%d\r\n\r\n",
                                    hc->s->hostname, (int)hc->s->port);
            }
            method = "OPTIONS";
            break;

        case HEAD:
            method = "HEAD";
            /* fallthru */
        case GET:
            if (!method) { /* did we fall thru? If not, we are GET */
                method = "GET";
            }
            if (!wctx->req) {
                wctx->req = apr_psprintf(ctx->p,
                                   "%s %s%s%s HTTP/1.0\r\nHost: %s:%d\r\n\r\n",
                                   method,
                                   (wctx->path ? wctx->path : ""),
                                   (wctx->path && *hc->s->hcuri ? "/" : "" ),
                                   (*hc->s->hcuri ? hc->s->hcuri : ""),
                                   hc->s->hostname, (int)hc->s->port);
            }
            break;

        default:
            return backend_cleanup("HCOH", backend, ctx->s, !OK);
            break;
    }

    hc_send(ctx, ptemp, wctx->req, backend);

    r = create_request_rec(ptemp, backend->connection, method);
    if ((status = hc_read_headers(ctx, r)) != OK) {
        return backend_cleanup("HCOH", backend, ctx->s, status);
    }
    if (hc->s->method == GET) {
        if ((status = hc_read_body(ctx, r)) != OK) {
            return backend_cleanup("HCOH", backend, ctx->s, status);
        }
    }

    if (*worker->s->hcexpr &&
            (cond = (hc_condition_t *)apr_table_get(ctx->conditions, worker->s->hcexpr)) != NULL) {
        const char *err;
        int ok = ap_expr_exec(r, cond->pexpr, &err);
        if (ok > 0) {
            status = OK;
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                         "Condition %s for %s (%s): passed", worker->s->hcexpr,
                         hc->s->name, worker->s->name);
        } else if (ok < 0 || err) {
            status = !OK;
            ap_log_error(APLOG_MARK, APLOG_INFO, 0, ctx->s, APLOGNO(03301)
                         "Error on checking condition %s for %s (%s): %s", worker->s->hcexpr,
                         hc->s->name, worker->s->name, err);
        } else {
            ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, ctx->s,
                         "Condition %s for %s (%s) : failed", worker->s->hcexpr,
                         hc->s->name, worker->s->name);
            status = !OK;
        }
    } else if (r->status < 200 || r->status > 399) {
        status = !OK;
    }
    return backend_cleanup("HCOH", backend, ctx->s, status);
}