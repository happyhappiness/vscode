int APR_THREAD_FUNC WriteClient(isapi_cid    *cid,
                                void         *buf_ptr,
                                apr_uint32_t *size_arg,
                                apr_uint32_t  flags)
{
    request_rec *r = cid->r;
    conn_rec *c = r->connection;
    apr_uint32_t buf_size = *size_arg;
    char *buf_data = (char*)buf_ptr;
    apr_bucket_brigade *bb;
    apr_bucket *b;
    apr_status_t rv;

    if (!cid->headers_set) {
        /* It appears that the foxisapi module and other clients
         * presume that WriteClient("headers\n\nbody") will work.
         * Parse them out, or die trying.
         */
        apr_ssize_t ate;
        ate = send_response_header(cid, NULL, buf_data, 0, buf_size);
        if (ate < 0) {
            apr_set_os_error(APR_FROM_OS_ERROR(ERROR_INVALID_PARAMETER));
            return 0;
        }

        buf_data += ate;
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