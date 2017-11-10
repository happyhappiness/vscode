static int sendfile_handler(request_rec *r, a_file *file)
{
#if APR_HAS_SENDFILE
    conn_rec *c = r->connection;
    apr_bucket *b;
    apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);

    apr_brigade_insert_file(bb, file->file, 0, file->finfo.size, r->pool);

    b = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS)
        return AP_FILTER_ERROR;
#endif
    return OK;
}