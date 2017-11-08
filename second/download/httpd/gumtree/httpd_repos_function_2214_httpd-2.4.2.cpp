static apr_status_t send_downstream(ap_filter_t *f, const char *tmp, apr_size_t len)
{
    request_rec *r = f->r;
    conn_rec *c = r->connection;
    apr_bucket *b;

    b = apr_bucket_transient_create(tmp, len, c->bucket_alloc);
    return send_bucket_downstream(f, b);
}