        /*
         * If we already send data, signal a broken backend connection
         * upwards in the chain.
         */
        if (data_sent) {
            ap_proxy_backend_broke(r, output_brigade);
        } else if (!send_body && (is_idempotent(r) == METHOD_IDEMPOTENT)) {
            /*
             * This is only non fatal when we have not sent (parts) of a possible
             * request body so far (we do not store it and thus cannot sent it
             * again) and the method is idempotent. In this case we can dare to
             * retry it with a different worker if we are a balancer member.
             */
            rv = HTTP_SERVICE_UNAVAILABLE;
        } else {
            rv = HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    else if (client_failed) {
        int level = (r->connection->aborted) ? APLOG_DEBUG : APLOG_ERR;
        ap_log_error(APLOG_MARK, level, status, r->server,
                     "dialog with client %pI failed",
                     r->connection->remote_addr);
        if (rv == OK) {
            rv = HTTP_BAD_REQUEST;
        }
    }

    /*
     * Ensure that we sent an EOS bucket thru the filter chain, if we already
     * have sent some data. Maybe ap_proxy_backend_broke was called and added
     * one to the brigade already (no longer making it empty). So we should
     * not do this in this case.
     */
    if (data_sent && !r->eos_sent && !r->connection->aborted
            && APR_BRIGADE_EMPTY(output_brigade)) {
        e = apr_bucket_eos_create(r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(output_brigade, e);
    }

    /* If we have added something to the brigade above, send it */
    if (!APR_BRIGADE_EMPTY(output_brigade)
        && ap_pass_brigade(r->output_filters, output_brigade) != APR_SUCCESS) {
        rv = AP_FILTER_ERROR;
    }

    apr_brigade_destroy(output_brigade);

    return rv;
}

/*
 * This handles ajp:// URLs
 */
