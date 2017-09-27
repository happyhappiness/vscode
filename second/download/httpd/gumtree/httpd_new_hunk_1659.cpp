        /*
         * If we already send data, signal a broken backend connection
         * upwards in the chain.
         */
        if (data_sent) {
            ap_proxy_backend_broke(r, output_brigade);
        } else
            rv = HTTP_SERVICE_UNAVAILABLE;
    }

    /*
     * Ensure that we sent an EOS bucket thru the filter chain, if we already
     * have sent some data. Maybe ap_proxy_backend_broke was called and added
     * one to the brigade already (no longer making it empty). So we should
     * not do this in this case.
     */
    if (data_sent && !r->eos_sent && APR_BRIGADE_EMPTY(output_brigade)) {
        e = apr_bucket_eos_create(r->connection->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(output_brigade, e);
    }

    /* If we have added something to the brigade above, sent it */
    if (!APR_BRIGADE_EMPTY(output_brigade))
        ap_pass_brigade(r->output_filters, output_brigade);

    apr_brigade_destroy(output_brigade);

    if (apr_table_get(r->subprocess_env, "proxy-nokeepalive")) {
        conn->close++;
    }

    return rv;
}

/*
 * This handles ajp:// URLs
 */
