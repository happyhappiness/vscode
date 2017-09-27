    /* add empty line at the end of the headers */
    e = apr_bucket_immortal_create(ASCII_CRLF, 2, bucket_alloc);
    APR_BRIGADE_INSERT_TAIL(header_brigade, e);
}

static int pass_brigade(apr_bucket_alloc_t *bucket_alloc,
                                 request_rec *r, proxy_conn_rec *conn,
                                 conn_rec *origin, apr_bucket_brigade *bb,
                                 int flush)
{
    apr_status_t status;
    apr_off_t transferred;

    if (flush) {
        apr_bucket *e = apr_bucket_flush_create(bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);
    }
    apr_brigade_length(bb, 0, &transferred);
    if (transferred != -1)
        conn->worker->s->transferred += transferred;
    status = ap_pass_brigade(origin->output_filters, bb);
    if (status != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                     "proxy: pass request body failed to %pI (%s)",
                     conn->addr, conn->hostname);
        if (origin->aborted) { 
            return APR_STATUS_IS_TIMEUP(status) ? HTTP_GATEWAY_TIME_OUT : HTTP_BAD_GATEWAY;
        }
        else { 
            return HTTP_BAD_REQUEST; 
        }
    }
    apr_brigade_cleanup(bb);
    return OK;
}

