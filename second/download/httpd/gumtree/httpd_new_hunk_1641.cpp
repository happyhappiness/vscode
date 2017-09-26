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
                /* AJP13_SEND_HEADERS: process them */
                status = ajp_parse_header(r, conf, conn->data);
                if (status != APR_SUCCESS) {
                    backend_failed = 1;
                }
                break;
            case CMD_AJP13_SEND_BODY_CHUNK:
                /* AJP13_SEND_BODY_CHUNK: piece of data */
                status = ajp_parse_data(r, conn->data, &size, &buff);
                if (status == APR_SUCCESS) {
