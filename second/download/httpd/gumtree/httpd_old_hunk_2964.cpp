            case CMD_AJP13_GET_BODY_CHUNK:
                if (havebody) {
                    if (APR_BUCKET_IS_EOS(APR_BRIGADE_LAST(input_brigade))) {
                        /* This is the end */
                        bufsiz = 0;
                        havebody = 0;
                        ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
                                     "proxy: APR_BUCKET_IS_EOS");
                    } else {
                        status = ap_get_brigade(r->input_filters, input_brigade,
                                                AP_MODE_READBYTES,
                                                APR_BLOCK_READ,
                                                maxsize - AJP_HEADER_SZ);
                        if (status != APR_SUCCESS) {
                            ap_log_error(APLOG_MARK, APLOG_DEBUG, status,
                                         r->server,
                                         "ap_get_brigade failed");
                            output_failed = 1;
                            break;
                        }
                        bufsiz = maxsize;
                        status = apr_brigade_flatten(input_brigade, buff,
                                                     &bufsiz);
                        apr_brigade_cleanup(input_brigade);
                        if (status != APR_SUCCESS) {
                            ap_log_error(APLOG_MARK, APLOG_DEBUG, status,
                                         r->server,
                                         "apr_brigade_flatten failed");
                            output_failed = 1;
                            break;
                        }
                    }

                    ajp_msg_reset(msg);
                    /* will go in ajp_send_data_msg */
                    status = ajp_send_data_msg(conn->sock, msg, bufsiz);
                    if (status != APR_SUCCESS) {
                        ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
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
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
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
                    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "proxy: Backend sent headers twice.");
                    break;
                }
                /* AJP13_SEND_HEADERS: process them */
                status = ajp_parse_header(r, conf, conn->data);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                headers_sent = 1;
                break;
            case CMD_AJP13_SEND_BODY_CHUNK:
                /* AJP13_SEND_BODY_CHUNK: piece of data */
                status = ajp_parse_data(r, conn->data, &size, &send_body_chunk_buff);
                if (status == APR_SUCCESS) {
                    /* AJP13_SEND_BODY_CHUNK with zero length
                     * is explicit flush message
                     */
                    if (size == 0) {
                        if (headers_sent) {
                            e = apr_bucket_flush_create(r->connection->bucket_alloc);
                            APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                        }
                        else {
                            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                 "Ignoring flush message received before headers");
                        }
                    }
                    else {
                        apr_status_t rv;

                        e = apr_bucket_transient_create(send_body_chunk_buff, size,
                                                    r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(output_brigade, e);

                        if ((conn->worker->flush_packets == flush_on) ||
                            ((conn->worker->flush_packets == flush_auto) &&
                            ((rv = apr_poll(conn_poll, 1, &conn_poll_fd,
                                             conn->worker->flush_wait))
                                             != APR_SUCCESS) &&
                              APR_STATUS_IS_TIMEUP(rv))) {
                            e = apr_bucket_flush_create(r->connection->bucket_alloc);
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
                    output_failed = 1;
                }
                /* XXX: what about flush here? See mod_jk */
                data_sent = 1;
                request_ended = 1;
                break;
            default:
                backend_failed = 1;
                break;
        }
