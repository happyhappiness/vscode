        rv = HTTP_INTERNAL_SERVER_ERROR ;
        break;
    }

    if (rv != OK) {
        /* apr_status_t value has been logged in lower level method */
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01097)
                      "pass request body failed to %pI (%s) from %s (%s)",
                      p_conn->addr, p_conn->hostname ? p_conn->hostname: "",
                      c->client_ip, c->remote_host ? c->remote_host: "");
        return rv;
    }

    return OK;
}

/*
 * If the date is a valid RFC 850 date or asctime() date, then it
 * is converted to the RFC 1123 format.
 */
static const char *date_canon(apr_pool_t *p, const char *date)
{
    apr_status_t rv;
    char* ndate;

    apr_time_t time = apr_date_parse_http(date);
    if (!time) {
        return date;
    }

    ndate = apr_palloc(p, APR_RFC822_DATE_LEN);
    rv = apr_rfc822_date(ndate, time);
    if (rv != APR_SUCCESS) {
        return date;
    }

    return ndate;
}

static request_rec *make_fake_req(conn_rec *c, request_rec *r)
{
    apr_pool_t *pool;
    request_rec *rp;

    apr_pool_create(&pool, c->pool);

    rp = apr_pcalloc(pool, sizeof(*r));

    rp->pool            = pool;
    rp->status          = HTTP_OK;

    rp->headers_in      = apr_table_make(pool, 50);
    rp->subprocess_env  = apr_table_make(pool, 50);
    rp->headers_out     = apr_table_make(pool, 12);
    rp->err_headers_out = apr_table_make(pool, 5);
    rp->notes           = apr_table_make(pool, 5);

    rp->server = r->server;
    rp->log = r->log;
    rp->proxyreq = r->proxyreq;
    rp->request_time = r->request_time;
    rp->connection      = c;
    rp->output_filters  = c->output_filters;
    rp->input_filters   = c->input_filters;
    rp->proto_output_filters  = c->output_filters;
    rp->proto_input_filters   = c->input_filters;
    rp->useragent_ip = c->client_ip;
    rp->useragent_addr = c->client_addr;

    rp->request_config  = ap_create_request_config(pool);
    proxy_run_create_req(r, rp);

    return rp;
}

static void process_proxy_header(request_rec *r, proxy_dir_conf *c,
                                 const char *key, const char *value)
{
    static const char *date_hdrs[]
        = { "Date", "Expires", "Last-Modified", NULL };
    static const struct {
