                                apr_bucket *tmp_b;
                                apr_brigade_cleanup(ob);
                                tmp_b = apr_bucket_eos_create(c->bucket_alloc);
                                APR_BRIGADE_INSERT_TAIL(ob, tmp_b);
                                r->status = status;
                                ap_pass_brigade(r->output_filters, ob);
                                if (status == HTTP_NOT_MODIFIED) {
                                    /* The 304 response MUST NOT contain
                                     * a message-body, ignore it. */
                                    ignore_body = 1;
                                }
                                else {
                                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
                                                    "Error parsing script headers");
                                    rv = APR_EINVAL;
                                }
                                break;
                            }

                            if (conf->error_override &&
                                ap_is_HTTP_ERROR(r->status)) {
                                /*
