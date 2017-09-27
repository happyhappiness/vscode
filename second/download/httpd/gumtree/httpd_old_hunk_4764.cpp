                            /* suck in all the rest */
                            if (status != OK) {
                                apr_bucket *tmp_b;
                                apr_brigade_cleanup(ob);
                                tmp_b = apr_bucket_eos_create(c->bucket_alloc);
                                APR_BRIGADE_INSERT_TAIL(ob, tmp_b);
                                ap_pass_brigade(r->output_filters, ob);
                                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
                                              "Error parsing script headers");
                                r->status = status;
                                rv = APR_EINVAL;
                                break;
                            }

                            if (conf->error_override &&
                                ap_is_HTTP_ERROR(r->status)) {
