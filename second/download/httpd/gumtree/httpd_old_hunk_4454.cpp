
                                *has_responded = 1;
                                r->status = status;
                                rv = ap_pass_brigade(r->output_filters, ob);
                                if (rv != APR_SUCCESS) {
                                    *err = "passing headers brigade to output filters";
                                }
                                else if (status == HTTP_NOT_MODIFIED) {
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
                                 * set script_error_status to discard
                                 * everything after the headers
                                 */
                                script_error_status = r->status;
                                /*
