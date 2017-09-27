
                                *has_responded = 1;
                                r->status = status;
                                rv = ap_pass_brigade(r->output_filters, ob);
                                if (rv != APR_SUCCESS) {
                                    *err = "passing headers brigade to output filters";
                                    break;
                                }
                                else if (status == HTTP_NOT_MODIFIED
                                         || status == HTTP_PRECONDITION_FAILED) {
                                    /* Special 'status' cases handled:
                                     * 1) HTTP 304 response MUST NOT contain
                                     *    a message-body, ignore it.
                                     * 2) HTTP 412 response.
                                     * The break is not added since there might
                                     * be more bytes to read from the FCGI
                                     * connection. Even if the message-body is
                                     * ignored (and the EOS bucket has already
                                     * been sent) we want to avoid subsequent
                                     * bogus reads. */
                                    ignore_body = 1;
                                }
                                else {
                                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01070)
                                                    "Error parsing script headers");
                                    rv = APR_EINVAL;
                                    break;
                                }
                            }

                            if (conf->error_override
                                && ap_is_HTTP_ERROR(r->status) && ap_is_initial_req(r)) {
                                /*
                                 * set script_error_status to discard
                                 * everything after the headers
                                 */
                                script_error_status = r->status;
                                /*
