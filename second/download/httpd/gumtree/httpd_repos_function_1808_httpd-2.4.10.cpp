static apr_status_t send_416(ap_filter_t *f, apr_bucket_brigade *tmpbb)
{
    apr_bucket *e;
    conn_rec *c = f->r->connection;
    ap_remove_output_filter(f);
    f->r->status = HTTP_OK;
    e = ap_bucket_error_create(HTTP_RANGE_NOT_SATISFIABLE, NULL,
                               f->r->pool, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(tmpbb, e);
    e = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(tmpbb, e);
    return ap_pass_brigade(f->next, tmpbb);
}