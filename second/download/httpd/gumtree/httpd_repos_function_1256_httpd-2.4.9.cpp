static int mmap_handler(request_rec *r, a_file *file)
{
#if APR_HAS_MMAP
    conn_rec *c = r->connection;
    apr_bucket *b;
    apr_mmap_t *mm;
    apr_bucket_brigade *bb = apr_brigade_create(r->pool, c->bucket_alloc);

    apr_mmap_dup(&mm, file->mm, r->pool);
    b = apr_bucket_mmap_create(mm, 0, (apr_size_t)file->finfo.size,
                               c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);
    b = apr_bucket_eos_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);

    if (ap_pass_brigade(r->output_filters, bb) != APR_SUCCESS)
        return HTTP_INTERNAL_SERVER_ERROR;
#endif
    return OK;
}