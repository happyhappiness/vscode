        }
#endif
        APR_BRIGADE_INSERT_TAIL(bb, e);
        e = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);

        status = ap_pass_brigade(r->output_filters, bb);
        if (status == APR_SUCCESS
            || r->status != HTTP_OK
            || c->aborted) {
            return OK; /* r->status will be respected */
        }
        else {
            /* no way to know what type of error occurred */
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r,
                          "default_handler: ap_pass_brigade returned %i",
                          status);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    else {              /* unusual method (not GET or POST) */
        if (r->method_number == M_INVALID) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid method in request %s", r->the_request);
            return HTTP_NOT_IMPLEMENTED;
