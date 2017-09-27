             * present in a request and the chunked transfer coding is not
             * the final encoding ...; the server MUST respond with the 400
             * (Bad Request) status code and then close the connection".
             */
            if (!(strcasecmp(tenc, "chunked") == 0 /* fast path */
                    || ap_find_last_token(r->pool, tenc, "chunked"))) {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02539)
                              "client sent unknown Transfer-Encoding "
                              "(%s): %s", tenc, r->uri);
                r->status = HTTP_BAD_REQUEST;
                conn->keepalive = AP_CONN_CLOSE;
                ap_send_error_response(r, 0);
                ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
