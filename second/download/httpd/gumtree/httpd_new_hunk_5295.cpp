
        for (pi = 0; pi < pollcnt; pi++) {
            const apr_pollfd_t *cur = &signalled[pi];

            if (cur->desc.s == sock) {
                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02446)
                                  "sock was readable");
                    rv = proxy_wstunnel_transfer(r, backconn, c, bb, "sock");
                }
                else if (pollevent & APR_POLLERR) {
                    rv = APR_EPIPE;
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02447)
                            "error on backconn");
                }
                else { 
                    rv = APR_EGENERAL;
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02605)
                            "unknown event on backconn %d", pollevent);
                }
            }
            else if (cur->desc.s == client_socket) {
                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02448)
                                  "client was readable");
                    rv = proxy_wstunnel_transfer(r, c, backconn, bb, "client");
                }
                else if (pollevent & APR_POLLERR) {
                    rv = APR_EPIPE;
                    c->aborted = 1;
                    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, APLOGNO(02607)
                            "error on client conn");
                }
                else { 
                    rv = APR_EGENERAL;
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02606)
                            "unknown event on client conn %d", pollevent);
                }
