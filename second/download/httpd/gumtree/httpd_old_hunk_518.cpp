        b = apr_bucket_transient_create(buf_data, buf_size, c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;
    }

    if ((flags & HSE_IO_ASYNC) && cid->completion) {
        if (rv == OK) {
            cid->completion(cid->ecb, cid->completion_arg, 
                            *size_arg, ERROR_SUCCESS);
        }
        else {
            cid->completion(cid->ecb, cid->completion_arg, 
                            *size_arg, ERROR_WRITE_FAULT);
        }
    }
    return (rv == OK);
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

    switch (HSE_code) {
    case HSE_REQ_SEND_URL_REDIRECT_RESP:
        /* Set the status to be returned when the HttpExtensionProc()
         * is done.
         * WARNING: Microsoft now advertises HSE_REQ_SEND_URL_REDIRECT_RESP
