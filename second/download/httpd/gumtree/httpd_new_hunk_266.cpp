                     "proxy: request failed to %pI (%s)",
                     p_conn->addr, p_conn->name);
        return status;
    }

    /* send the request data, if any. */
    seen_eos = 0;
    do {
        status = ap_get_brigade(r->input_filters, bb, AP_MODE_READBYTES,
                                APR_BLOCK_READ, HUGE_STRING_LEN);

        if (status != APR_SUCCESS) {
            return status;
        }

        /* If this brigade contain EOS, either stop or remove it. */
        if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(bb))) {
            /* As a shortcut, if this brigade is simply an EOS bucket,
             * don't send anything down the filter chain.
             */
            if (APR_BUCKET_IS_EOS(APR_BRIGADE_FIRST(bb))) {
                break;
            }

            /* We can't pass this EOS to the output_filters. */
            APR_BUCKET_REMOVE(APR_BRIGADE_LAST(bb));
            seen_eos = 1;
        }

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
    } while (!seen_eos);

    return APR_SUCCESS;
}

static
apr_status_t ap_proxy_http_process_response(apr_pool_t * p, request_rec *r,
                                            proxy_http_conn_t *p_conn,
