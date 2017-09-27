
    /* add empty line at the end of the headers */
    e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
}


#define MAX_MEM_SPOOL 16384

static int stream_reqbody_chunked(apr_pool_t *p,
                                           request_rec *r,
                                           proxy_conn_rec *p_conn,
