static int hc_send(request_rec *r, const char *out, apr_bucket_brigade *bb)
{
    apr_status_t rv;
    conn_rec *c = r->connection;
    apr_bucket_alloc_t *ba = c->bucket_alloc;
    ap_log_error(APLOG_MARK, APLOG_TRACE7, 0, r->server, "%s", out);
    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(out, strlen(out),
                                                       r->pool, ba));
    APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_flush_create(ba));
    rv = ap_pass_brigade(c->output_filters, bb);
    apr_brigade_cleanup(bb);
    return (rv) ? !OK : OK;
}