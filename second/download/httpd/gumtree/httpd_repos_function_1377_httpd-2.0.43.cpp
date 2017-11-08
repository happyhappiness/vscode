int APR_THREAD_FUNC WriteClient(isapi_cid    *cid, 
                                void         *buf_data, 
                                apr_uint32_t *buf_size, 
                                apr_uint32_t  flags)
{
    request_rec *r = cid->r;
    conn_rec *c = r->connection;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    apr_status_t rv;

    bb = apr_brigade_create(r->pool, c->bucket_alloc);
    b = apr_bucket_transient_create(buf_data, *buf_size, c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);
    b = apr_bucket_flush_create(c->bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(bb, b);
    rv = ap_pass_brigade(r->output_filters, bb);

    if ((flags & HSE_IO_ASYNC) && cid->completion) {
        if (rv == OK) {
            cid->completion(cid->ecb, cid->completion_arg, 
                            *buf_size, ERROR_SUCCESS);
        }
        else {
            cid->completion(cid->ecb, cid->completion_arg, 
                            *buf_size, ERROR_WRITE_FAULT);
        }
    }
    return (rv == OK);
}