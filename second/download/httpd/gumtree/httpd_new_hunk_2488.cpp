            b = apr_bucket_flush_create(c->bucket_alloc);
            APR_BRIGADE_INSERT_TAIL(bb, b);
            rv = ap_pass_brigade(cid->r->output_filters, bb);
            cid->response_sent = 1;
            if (rv != APR_SUCCESS)
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, r,
                              "ServerSupport function "
                              "HSE_REQ_SEND_RESPONSE_HEADER "
                              "ap_pass_brigade failed: %s", r->filename);
            return (rv == APR_SUCCESS);
        }
        /* Deliberately hold off sending 'just the headers' to begin to
         * accumulate the body and speed up the overall response, or at
