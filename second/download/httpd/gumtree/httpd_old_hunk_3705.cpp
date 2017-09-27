        b = apr_bucket_eos_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_TAIL(bb, b);
        rv = ap_pass_brigade(r->output_filters, bb);
        if (rv != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01236)
                          "mod_asis: ap_pass_brigade failed for file %s", r->filename);
            return HTTP_INTERNAL_SERVER_ERROR;
        }
    }
    else {
        apr_file_close(f);
    }

