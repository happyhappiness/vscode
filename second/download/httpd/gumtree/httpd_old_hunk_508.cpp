        }
#endif
        APR_BRIGADE_INSERT_TAIL(bb, e);
        e = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, e);

        return ap_pass_brigade(r->output_filters, bb);
    }
    else {              /* unusual method (not GET or POST) */
        if (r->method_number == M_INVALID) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "Invalid method in request %s", r->the_request);
            return HTTP_NOT_IMPLEMENTED;
