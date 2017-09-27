        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        cid->response_sent = 1;

        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                          "ISAPI: ap_pass_brigade failed to "
                          "complete the response: %s ", r->filename);
        }

        return OK; /* NOT r->status, even if it has changed. */
    }

