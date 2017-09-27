                    e = apr_bucket_eos_create(r->connection->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                    if (ap_pass_brigade(r->output_filters,
                                        output_brigade) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      "proxy: error processing end");
                        output_failed = 1;
                    }
                    /* XXX: what about flush here? See mod_jk */
                    data_sent = 1;
                }
                request_ended = 1;
                break;
