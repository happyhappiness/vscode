                }
                break;
            case CMD_AJP13_SEND_BODY_CHUNK:
                /* AJP13_SEND_BODY_CHUNK: piece of data */
                status = ajp_parse_data(r, conn->data, &size, &buff);
                if (status == APR_SUCCESS) {
                    if (size == 0) {
                        /* AJP13_SEND_BODY_CHUNK with zero length
                         * is explicit flush message
                         */
                        e = apr_bucket_flush_create(r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                    }
                    else {
                        e = apr_bucket_transient_create(buff, size,
                                                    r->connection->bucket_alloc);
                        APR_BRIGADE_INSERT_TAIL(output_brigade, e);

                        if ((conn->worker->flush_packets == flush_on) ||
                            ((conn->worker->flush_packets == flush_auto) &&
                            (apr_poll(conn_poll, 1, &conn_poll_fd,
                                      conn->worker->flush_wait)
                                        == APR_TIMEUP) ) ) {
                            e = apr_bucket_flush_create(r->connection->bucket_alloc);
                            APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                        }
                        apr_brigade_length(output_brigade, 0, &bb_len);
                        if (bb_len != -1)
                            conn->worker->s->read += bb_len;
                    }
                    if (ap_pass_brigade(r->output_filters,
                                        output_brigade) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                      "proxy: error processing body");
                        isok = 0;
                    }
