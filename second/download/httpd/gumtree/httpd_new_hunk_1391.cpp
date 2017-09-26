                            output_failed = 1;
                        }
                        data_sent = 1;
                        apr_brigade_cleanup(output_brigade);
                    }
                }
            }
                else {
                    backend_failed = 1;
                }
                break;
            case CMD_AJP13_END_RESPONSE:
                status = ajp_parse_reuse(r, conn->data, &conn_reuse);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                /* If we are overriding the errors, we must not send anything to
                 * the client, especially as the brigade already contains headers.
                 * So do nothing here, and it will be cleaned up below.
                 */
                if (!psf->error_override || !ap_is_HTTP_ERROR(r->status)) {
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
            default:
                backend_failed = 1;
                break;
        }
