                    else {
                        const char *buf;
                        apr_size_t len = 0;
                        rv = apr_bucket_read(bucket, &buf, &len,
                                             APR_BLOCK_READ);
                        if (rv != APR_SUCCESS) {
                            ap_log_cerror(APLOG_MARK, APLOG_ERR, rv,
                                          c, "core_output_filter:"
                                          " Error reading from bucket.");
                            return HTTP_INTERNAL_SERVER_ERROR;
                        }
                    }
                }
            }
            if (!ctx->deferred_write_pool) {
