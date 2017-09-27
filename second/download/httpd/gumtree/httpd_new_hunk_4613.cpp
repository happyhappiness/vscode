    } else {
        return !OK;
    }
    /* OK, 1st line is OK... scarf in the headers */
    while ((len = ap_getline(buffer, sizeof(buffer), r, 1)) > 0) {
        char *value, *end;
        ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, r->server, "%.*s",
                     len, buffer);
        if (!(value = strchr(buffer, ':'))) {
            return !OK;
        }
        *value = '\0';
        ++value;
        while (apr_isspace(*value))
            ++value;            /* Skip to start of value   */
        for (end = &value[strlen(value)-1]; end > value && apr_isspace(*end); --end)
            *end = '\0';
        apr_table_add(r->headers_out, buffer, value);
    }
    return OK;
}

static int hc_read_body(request_rec *r, apr_bucket_brigade *bb)
{
    apr_status_t rv = APR_SUCCESS;
    int seen_eos = 0;

    do {
        apr_size_t len = HUGE_STRING_LEN;

        apr_brigade_cleanup(bb);
        rv = ap_get_brigade(r->proto_input_filters, bb, AP_MODE_READBYTES,
                            APR_BLOCK_READ, len);

        if (rv != APR_SUCCESS) {
            if (APR_STATUS_IS_EOF(rv)) {
                rv = APR_SUCCESS;
                break;
            }
            ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, r->server, APLOGNO(03300)
                          "Error reading response body");
            break;
        }

        while (!APR_BRIGADE_EMPTY(bb)) {
            apr_bucket *bucket = APR_BRIGADE_FIRST(bb);
            if (APR_BUCKET_IS_EOS(bucket)) {
                seen_eos = 1;
                break;
            }
            if (APR_BUCKET_IS_FLUSH(bucket)) {
                apr_bucket_delete(bucket);
                continue;
            }
            APR_BUCKET_REMOVE(bucket);
            APR_BRIGADE_INSERT_TAIL(r->kept_body, bucket);
        }
    }
    while (!seen_eos);
    apr_brigade_cleanup(bb);
    return (rv == APR_SUCCESS ? OK : !OK);
}

/*
 * Send the HTTP OPTIONS, HEAD or GET request to the backend
 * server associated w/ worker. If we have Conditions,
 * then apply those to the resulting response, otherwise
 * any status code 2xx or 3xx is considered "passing"
 */
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

static void * APR_THREAD_FUNC hc_check(apr_thread_t *thread, void *b)
{
    baton_t *baton = (baton_t *)b;
    server_rec *s = baton->ctx->s;
    proxy_worker *worker = baton->worker;
    proxy_worker *hc = baton->hc;
    apr_time_t now = baton->now;
    apr_status_t rv;

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(03256)
                 "%sHealth checking %s", (thread ? "Threaded " : ""),
                 worker->s->name);

    if (hc->s->method == TCP) {
        rv = hc_check_tcp(baton);
    }
    else {
        rv = hc_check_http(baton);
    }
    if (rv == APR_ENOTIMPL) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(03257)
                         "Somehow tried to use unimplemented hcheck method: %d",
                         (int)hc->s->method);
        apr_pool_destroy(baton->ptemp);
        return NULL;
    }
    /* what state are we in ? */
    if (PROXY_WORKER_IS_HCFAILED(worker)) {
        if (rv == APR_SUCCESS) {
            worker->s->pcount += 1;
