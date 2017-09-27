
    if (old_cl_val) {
        char *endstr;

        add_cl(p, bucket_alloc, header_brigade, old_cl_val);
        status = apr_strtoff(&cl_val, old_cl_val, &endstr, 10);
        
        if (status || *endstr || endstr == old_cl_val || cl_val < 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                          "proxy: could not parse request Content-Length (%s)",
                          old_cl_val);
            return HTTP_BAD_REQUEST;
        }
    }
    terminate_headers(bucket_alloc, header_brigade);

