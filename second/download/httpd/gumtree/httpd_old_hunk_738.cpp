                    if (partial_send_okay) {
                        split = b;
                        more = apr_brigade_split(b, e);
                        flush = 1;
                        break;
                    }
                }
                else if (rv != APR_EOF) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                                  "ap_content_length_filter: "
                                  "apr_bucket_read() failed");
                    return rv;
