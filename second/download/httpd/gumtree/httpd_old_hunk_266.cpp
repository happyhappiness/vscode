                     "proxy: request failed to %pI (%s)",
                     p_conn->addr, p_conn->name);
        return status;
    }

    /* send the request data, if any. */
    if (ap_should_client_block(r)) {
        while ((counter = ap_get_client_block(r, buffer, sizeof(buffer))) > 0) {
            e = apr_bucket_pool_create(buffer, counter, p, c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            e = apr_bucket_flush_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, e);
            status = ap_pass_brigade(origin->output_filters, bb);
            if (status != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, status, r->server,
                             "proxy: pass request data failed to %pI (%s)",
                             p_conn->addr, p_conn->name);
                return status;
            }
            apr_brigade_cleanup(bb);
        }
    }
    return APR_SUCCESS;
}

static
apr_status_t ap_proxy_http_process_response(apr_pool_t * p, request_rec *r,
                                            proxy_http_conn_t *p_conn,
