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
