ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                              "ap_content_length_filter: "
                              "apr_bucket_read() failed");