        return ate + termch - head;
    }
    return ate;
}

int APR_THREAD_FUNC WriteClient(isapi_cid    *cid,
                                void         *buf_data,
                                apr_uint32_t *size_arg,
                                apr_uint32_t  flags)
{
    request_rec *r = cid->r;
    conn_rec *c = r->connection;
    apr_uint32_t buf_size = *size_arg;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    apr_status_t rv;

    if (!cid->headers_set) {
        /* It appears that the foxisapi module and other clients
         * presume that WriteClient("headers\n\nbody") will work.
         * Parse them out, or die trying.
         */
        apr_ssize_t ate;
        ate = send_response_header(cid, NULL, (char*)buf_data,
                                   0, buf_size);
        if (ate < 0) {
            SetLastError(ERROR_INVALID_PARAMETER);
            return 0;
        }

        (char*)buf_data += ate;
        buf_size -= ate;
    }

    if (buf_size) {
        bb = apr_brigade_create(r->pool, c->bucket_alloc);
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
                                          void         *buf_data,
                                          apr_uint32_t *buf_size,
                                          apr_uint32_t *data_type)
{
    request_rec *r = cid->r;
    conn_rec *c = r->connection;
    request_rec *subreq;

    switch (HSE_code) {
    case HSE_REQ_SEND_URL_REDIRECT_RESP:
        /* Set the status to be returned when the HttpExtensionProc()
         * is done.
         * WARNING: Microsoft now advertises HSE_REQ_SEND_URL_REDIRECT_RESP
