
            if (cur->desc.s == sock) {
                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02446)
                                  "sock was readable");
                    done |= proxy_wstunnel_transfer(r, backconn, c, bb,
                                                    "sock", NULL) != APR_SUCCESS;
                }
                else if (pollevent & APR_POLLERR) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02447)
                            "error on backconn");
                    backconn->aborted = 1;
                    done = 1;
                }
                else { 
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02605)
                            "unknown event on backconn %d", pollevent);
                    done = 1;
                }
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
                }
                else { 
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02606)
                            "unknown event on client conn %d", pollevent);
                    done = 1;
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(02449)
                              "unknown socket in pollset");
                done = 1;
            }

        }
    } while (!done);

    ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
                  "finished with poll() - cleaning up");

    if (!replied) {
        return HTTP_BAD_GATEWAY;
    }
    else {
        return OK;
    }

    return OK;
}

/*
 */
static int proxy_wstunnel_handler(request_rec *r, proxy_worker *worker,
