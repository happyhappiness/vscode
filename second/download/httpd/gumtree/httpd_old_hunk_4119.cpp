            }
            else if (cur->desc.s == client_socket) {
                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02448)
                                  "client was readable");
                    done |= proxy_wstunnel_transfer(r, c, backconn, bb,
                                                    "client", &replied) != APR_SUCCESS;
                }
                else if (pollevent & APR_POLLERR) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02607)
                            "error on client conn");
                    c->aborted = 1;
                    done = 1;
