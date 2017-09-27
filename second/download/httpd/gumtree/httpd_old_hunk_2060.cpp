                            conn->worker->s->read += bb_len;
                    }
                    if (ap_pass_brigade(r->output_filters,
                                        output_brigade) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                      "proxy: error processing body");
                        isok = 0;
                    }
                    data_sent = 1;
                    apr_brigade_cleanup(output_brigade);
                }
                else {
                    isok = 0;
                }
                break;
            case CMD_AJP13_END_RESPONSE:
                e = apr_bucket_eos_create(r->connection->bucket_alloc);
                APR_BRIGADE_INSERT_TAIL(output_brigade, e);
                if (ap_pass_brigade(r->output_filters,
                                    output_brigade) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "proxy: error processing body");
                    isok = 0;
                }
                /* XXX: what about flush here? See mod_jk */
                data_sent = 1;
                break;
            default:
                isok = 0;
                break;
        }

        /*
         * If connection has been aborted by client: Stop working.
         * Nevertheless, we regard our operation so far as a success:
         * So do not set isok to 0 and set result to CMD_AJP13_END_RESPONSE
         * But: Close this connection to the backend.
         */
        if (r->connection->aborted) {
            conn->close++;
            result = CMD_AJP13_END_RESPONSE;
            break;
        }

        if (!isok)
            break;

        if (result == CMD_AJP13_END_RESPONSE)
            break;

        /* read the response */
        status = ajp_read_header(conn->sock, r,
                                 (ajp_msg_t **)&(conn->data));
        if (status != APR_SUCCESS) {
            isok = 0;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
                         "ajp_read_header failed");
            break;
        }
        result = ajp_parse_type(r, conn->data);
    }
