                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
#ifdef DEBUGGING
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01025)
                                  "sock was readable");
#endif
                    rv = proxy_connect_transfer(r, backconn, c, bb, "sock");
                }
                else if (pollevent & APR_POLLERR) {
                    rv = APR_EPIPE;
                    backconn->aborted = 1;
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(01026)
                                  "err on backconn");
                }
            }
            else if (cur->desc.s == client_socket) {
                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
#ifdef DEBUGGING
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01027)
                                  "client was readable");
#endif
                    rv = proxy_connect_transfer(r, c, backconn, bb, "client");
                }
                else if (pollevent & APR_POLLERR) {
                    rv = APR_EPIPE;
                    c->aborted = 1;
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(01026)
                                  "err on client");
                }
            }
            else {
                rv = APR_EBADF;
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(01028)
                              "unknown socket in pollset");
            }

        }
        if (rv != APR_SUCCESS) {
            break;
        }
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                  "finished with poll() - cleaning up");

    /*
     * Step Five: Clean Up
