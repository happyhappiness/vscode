    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);

    return OK;
}

/* read available data (in blocks of CONN_BLKSZ) from c_i and copy to c_o */
static int proxy_connect_transfer(request_rec *r, conn_rec *c_i, conn_rec *c_o,
                                  apr_bucket_brigade *bb, char *name)
{
    int rv;
#ifdef DEBUGGING
    apr_off_t len;
#endif

    do {
        apr_brigade_cleanup(bb);
        rv = ap_get_brigade(c_i->input_filters, bb, AP_MODE_READBYTES,
                            APR_NONBLOCK_READ, CONN_BLKSZ);
        if (rv == APR_SUCCESS) {
            if (c_o->aborted)
                return APR_EPIPE;
            if (APR_BRIGADE_EMPTY(bb))
                break;
#ifdef DEBUGGING
            len = -1;
            apr_brigade_length(bb, 0, &len);
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01016)
                          "read %" APR_OFF_T_FMT
                          " bytes from %s", len, name);
#endif
            rv = ap_pass_brigade(c_o->output_filters, bb);
            if (rv == APR_SUCCESS) {
                ap_fflush(c_o->output_filters, bb);
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01017)
                              "error on %s - ap_pass_brigade",
                              name);
            }
        } else if (!APR_STATUS_IS_EAGAIN(rv)) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(01018)
                          "error on %s - ap_get_brigade",
                          name);
        }
    } while (rv == APR_SUCCESS);

    if (APR_STATUS_IS_EAGAIN(rv)) {
        rv = APR_SUCCESS;
    }
    return rv;
}

/* CONNECT handler */
static int proxy_connect_handler(request_rec *r, proxy_worker *worker,
                                 proxy_server_conf *conf,
                                 char *url, const char *proxyname,
                                 apr_port_t proxyport)
{
