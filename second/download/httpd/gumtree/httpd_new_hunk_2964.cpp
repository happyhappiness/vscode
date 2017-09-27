            case CMD_AJP13_GET_BODY_CHUNK:
                if (havebody) {
                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
                        /* This is the end */
                        bufsiz = 0;
                        havebody = 0;
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00879)
                                      "APR_BUCKET_IS_EOS");
                    } else {
                        status = ap_get_brigade(r->input_filters, input_brigade,
                                                AP_MODE_READBYTES,
                                                APR_BLOCK_READ,
                                                maxsize - AJP_HEADER_SZ);
                        if (status != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00880)
                                          "ap_get_brigade failed");
                            output_failed = 1;
                            break;
                        }
                        bufsiz = maxsize;
                        status = apr_brigade_flatten(input_brigade, buff,
                                                     &bufsiz);
                        apr_brigade_cleanup(input_brigade);
                        if (status != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00881)
                                         "apr_brigade_flatten failed");
                            output_failed = 1;
                            break;
                        }
                    }

                    ajp_msg_reset(msg);
                    /* will go in ajp_send_data_msg */
                    status = ajp_send_data_msg(conn->sock, msg, bufsiz);
                    ajp_msg_log(r, msg, "ajp_send_data_msg after CMD_AJP13_GET_BODY_CHUNK: ajp_ilink_send packet dump");
                    if (status != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00882)
                                      "ajp_send_data_msg failed");
                        backend_failed = 1;
                        break;
                    }
                    conn->worker->s->transferred += bufsiz;
                } else {
                    /*
                     * something is wrong TC asks for more body but we are
                     * already at the end of the body data
                     */
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00883)
                                  "ap_proxy_ajp_request error read after end");
                    backend_failed = 1;
                }
                break;
            case CMD_AJP13_SEND_HEADERS:
                if (headers_sent) {
                    /* Do not send anything to the client.
                     * Backend already send us the headers.
                     */
                    backend_failed = 1;
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00884)
                                  "Backend sent headers twice.");
                    break;
                }
                /* AJP13_SEND_HEADERS: process them */
                status = ajp_parse_header(r, conf, conn->data);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                else if ((r->status == 401) && conf->error_override) {
                    const char *buf;
                    const char *wa = "WWW-Authenticate";
                    if ((buf = apr_table_get(r->headers_out, wa))) {
                        apr_table_set(r->err_headers_out, wa, buf);
                    } else {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00885)
                                      "ap_proxy_ajp_request: origin server "
                                      "sent 401 without WWW-Authenticate header");
                    }
                }
                headers_sent = 1;
                break;
            case CMD_AJP13_SEND_BODY_CHUNK:
                /* AJP13_SEND_BODY_CHUNK: piece of data */
                status = ajp_parse_data(r, conn->data, &size, &send_body_chunk_buff);
                if (status == APR_SUCCESS) {
                    /* If we are overriding the errors, we can't put the content
                     * of the page into the brigade.
                     */
                    if (!conf->error_override || !ap_is_HTTP_ERROR(r->status)) {
                        /* AJP13_SEND_BODY_CHUNK with zero length
                         * is explicit flush message
                         */
                        if (size == 0) {
                            if (headers_sent) {
                                e = apr_bucket_flush_create(r->connection->bucket_alloc);
                                APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                            }
                            else {
                                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00886)
                                              "Ignoring flush message "
                                              "received before headers");
                            }
                        }
                        else {
                            apr_status_t rv;

                            /* Handle the case where the error document is itself reverse
                             * proxied and was successful. We must maintain any previous
                             * error status so that an underlying error (eg HTTP_NOT_FOUND)
                             * doesn't become an HTTP_OK.
                             */
                            if (conf->error_override && !ap_is_HTTP_ERROR(r->status)
                                    && ap_is_HTTP_ERROR(original_status)) {
                                r->status = original_status;
                                r->status_line = original_status_line;
                            }

                            e = apr_bucket_transient_create(send_body_chunk_buff, size,
                                                        r->connection->bucket_alloc);
                            APR_BRIGADE_INSERT_TAIL(output_brigade, e);

                            if ((conn->worker->s->flush_packets == flush_on) ||
                                ((conn->worker->s->flush_packets == flush_auto) &&
                                ((rv = apr_poll(conn_poll, 1, &conn_poll_fd,
                                                 conn->worker->s->flush_wait))
                                                 != APR_SUCCESS) &&
                                  APR_STATUS_IS_TIMEUP(rv))) {
                                e = apr_bucket_flush_create(r->connection->bucket_alloc);
                                APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                            }
                            apr_brigade_length(output_brigade, 0, &bb_len);
                            if (bb_len != -1)
                                conn->worker->s->read += bb_len;
                        }
                        if (headers_sent) {
                            if (ap_pass_brigade(r->output_filters,
                                                output_brigade) != APR_SUCCESS) {
                                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00887)
                                              "error processing body.%s",
                                              r->connection->aborted ?
                                              " Client aborted connection." : "");
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
                /* If we are overriding the errors, we must not send anything to
                 * the client, especially as the brigade already contains headers.
                 * So do nothing here, and it will be cleaned up below.
                 */
                status = ajp_parse_reuse(r, conn->data, &conn_reuse);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                if (!conf->error_override || !ap_is_HTTP_ERROR(r->status)) {
                    e = apr_bucket_eos_create(r->connection->bucket_alloc);
                    APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                    if (ap_pass_brigade(r->output_filters,
                                        output_brigade) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00888)
                                      "error processing end");
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
