                    ctx->data_sent = 1;
                }
                eblock = APR_BLOCK_READ;
                continue;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(00574)
                              "ap_content_length_filter: "
                              "apr_bucket_read() failed");
                return rv;
            }
        }
        else {
