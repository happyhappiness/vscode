                            APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                        }
                        apr_brigade_length(output_brigade, 0, &bb_len);
                        if (bb_len != -1)
                            conn->worker->s->read += bb_len;
                    }
                    if (ap_pass_brigade(r->output_filters,
                                        output_brigade) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                      "proxy: error processing body.%s",
                                      r->connection->aborted ?
                                      " Client aborted connection." : "");
                        output_failed = 1;
                    }
                    data_sent = 1;
                    apr_brigade_cleanup(output_brigade);
                }
                else {
                    backend_failed = 1;
                }
                break;
            case CMD_AJP13_END_RESPONSE:
                e = apr_bucket_eos_create(r->connection->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                if (ap_pass_brigade(r->output_filters,
                                    output_brigade) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                  "proxy: error processing end");
