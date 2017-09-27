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

#define MAX_MEM_SPOOL 16384

static int stream_reqbody_chunked(apr_pool_t *p,
                                           request_rec *r,
                                           proxy_conn_rec *p_conn,
                                           conn_rec *origin,
                                           apr_bucket_brigade *header_brigade,
                                           apr_bucket_brigade *input_brigade)
{
    int seen_eos = 0, rv = OK;
    apr_size_t hdr_len;
    apr_off_t bytes;
    apr_status_t status;
    apr_bucket_alloc_t *bucket_alloc = r->connection->bucket_alloc;
    apr_bucket_brigade *bb;
    apr_bucket *e;
