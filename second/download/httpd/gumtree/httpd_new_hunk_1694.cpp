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

#define MAX_MEM_SPOOL 16384

static int stream_reqbody_chunked(apr_pool_t *p,
