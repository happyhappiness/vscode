
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;
        if (rv != APR_SUCCESS)
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r, APLOGNO(03178)
                          "ServerSupportFunction "
                          "HSE_REQ_TRANSMIT_FILE "
                          "ap_pass_brigade failed: %s", r->filename);

        /* Use tf->pfnHseIO + tf->pContext, or if NULL, then use cid->fnIOComplete
         * pass pContect to the HseIO callback.
         */
