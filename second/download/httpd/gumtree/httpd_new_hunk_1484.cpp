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
