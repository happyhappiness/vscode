                            APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                        }
                        apr_brigade_length(output_brigade, 0, &bb_len);
                        if (bb_len != -1)
                            conn->worker->s->read += bb_len;
                    }
                    if (headers_sent) {
                        if (ap_pass_brigade(r->output_filters,
                                            output_brigade) != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                                          "proxy: error processing body.%s",
                                          r->connection->aborted ?
                                          " Client aborted connection." : "");
                            client_failed = 1;
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
                        client_failed = 1;
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

        /*
         * If connection has been aborted by client: Stop working.
         * Pretend we are done (data_sent) to avoid further processing.
         */
        if (r->connection->aborted) {
            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                          "client connection aborted");
            /* no response yet (or ever), set status for access log */
            if (!headers_sent) {
                r->status = HTTP_BAD_REQUEST;
            }
            client_failed = 1;
            /* return DONE */
            data_sent = 1;
            break;
        }

        /*
         * We either have finished successfully or we failed.
         * So bail out
         */
        if ((result == CMD_AJP13_END_RESPONSE)
                || backend_failed || client_failed)
            break;

        /* read the response */
        status = ajp_read_header(conn->sock, r, maxsize,
                                 (ajp_msg_t **)&(conn->data));
        if (status != APR_SUCCESS) {
