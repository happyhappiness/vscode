        b = apr_bucket_transient_create(buf_data, buf_size, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;
        if (rv != APR_SUCCESS)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ISAPI: WriteClient ap_pass_brigade "
                          "failed: %s", r->filename);
    }

    if ((flags & HSE_IO_ASYNC) && cid->completion) {
        if (rv == APR_SUCCESS) {
            cid->completion(cid->ecb, cid->completion_arg,
                            *size_arg, ERROR_SUCCESS);
        }
        else {
            cid->completion(cid->ecb, cid->completion_arg,
                            *size_arg, ERROR_WRITE_FAULT);
        }
    }
    return (rv == APR_SUCCESS);
}

/* A "safe" maximum bucket size, 1Gb */
#define MAX_BUCKET_SIZE (0x40000000)

apr_bucket *brigade_insert_file(apr_bucket_brigade *bb,
                                apr_file_t *f,
                                apr_off_t start,
                                apr_off_t length,
                                apr_pool_t *p)
{
    apr_bucket *e;

    if (sizeof(apr_off_t) == sizeof(apr_size_t) || length < MAX_BUCKET_SIZE) {
        e = apr_bucket_file_create(f, start, (apr_size_t)length, p, 
                                   bb->bucket_alloc);
    }
    else {
        /* Several buckets are needed. */        
        e = apr_bucket_file_create(f, start, MAX_BUCKET_SIZE, p, 
                                   bb->bucket_alloc);

        while (length > MAX_BUCKET_SIZE) {
            apr_bucket *ce;
            apr_bucket_copy(e, &ce);
            APR_BRIGADE_INSERT_TAIL(bb, ce);
            e->start += MAX_BUCKET_SIZE;
            length -= MAX_BUCKET_SIZE;
        }
        e->length = (apr_size_t)length; /* Resize just the last bucket */
    }
    
    APR_BRIGADE_INSERT_TAIL(bb, e);
    return e;
}

int APR_THREAD_FUNC ServerSupportFunction(isapi_cid    *cid,
                                          apr_uint32_t  HSE_code,
                                          void         *buf_ptr,
                                          apr_uint32_t *buf_size,
                                          apr_uint32_t *data_type)
{
    request_rec *r = cid->r;
    conn_rec *c = r->connection;
    char *buf_data = (char*)buf_ptr;
    request_rec *subreq;
    apr_status_t rv;

    switch (HSE_code) {
    case HSE_REQ_SEND_URL_REDIRECT_RESP:
        /* Set the status to be returned when the HttpExtensionProc()
         * is done.
         * WARNING: Microsoft now advertises HSE_REQ_SEND_URL_REDIRECT_RESP
