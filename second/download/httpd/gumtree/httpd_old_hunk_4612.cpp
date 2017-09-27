        return APR_EGENERAL;
    }
    return APR_SUCCESS;
}

static int hc_get_backend(const char *proxy_function, proxy_conn_rec **backend,
                          proxy_worker *hc, sctx_t *ctx)
{
    int status;
    status = ap_proxy_acquire_connection(proxy_function, backend, hc, ctx->s);
    if (status == OK) {
        (*backend)->addr = hc->cp->addr;
        (*backend)->pool = ctx->p;
        (*backend)->hostname = hc->s->hostname;
        if (strcmp(hc->s->scheme, "https") == 0) {
            if (!ap_proxy_ssl_enable(NULL)) {
                ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ctx->s, APLOGNO(03252)
                              "mod_ssl not configured?");
                return !OK;
            }
            (*backend)->is_ssl = 1;
        }

    }
    status = hc_determine_connection(ctx, hc);
    if (status == OK) {
        (*backend)->addr = hc->cp->addr;
    }
    return status;
}

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

static void hc_send(sctx_t *ctx, apr_pool_t *ptemp, const char *out, proxy_conn_rec *backend)
{
    apr_bucket_brigade *tmp_bb = apr_brigade_create(ptemp, ctx->ba);
    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, ctx->s, "%s", out);
    APR_BRIGADE_INSERT_TAIL(tmp_bb, apr_bucket_pool_create(out, strlen(out), ptemp,
                            ctx->ba));
    APR_BRIGADE_INSERT_TAIL(tmp_bb, apr_bucket_flush_create(ctx->ba));
    ap_pass_brigade(backend->connection->output_filters, tmp_bb);
    apr_brigade_destroy(tmp_bb);
}

static int hc_read_headers(sctx_t *ctx, request_rec *r)
{
    char buffer[HUGE_STRING_LEN];
    int len;

    len = ap_getline(buffer, sizeof(buffer), r, 1);
    if (len <= 0) {
        return !OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, ctx->s, APLOGNO(03254)
            "%s", buffer);
    /* for the below, see ap_proxy_http_process_response() */
    if (apr_date_checkmask(buffer, "HTTP/#.# ###*")) {
        int major;
        char keepchar;
        int proxy_status = OK;
        const char *proxy_status_line = NULL;
