                pollevent = cur->rtnevents;
                if (pollevent & (APR_POLLIN | APR_POLLHUP)) {
#ifdef DEBUGGING
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01027)
                                  "client was readable");
#endif
                    done |= proxy_connect_transfer(r, c, backconn, bb,
                                                   "client") != APR_SUCCESS;
                }
                else if (pollevent & APR_POLLERR) {
                    ap_log_rerror(APLOG_MARK, APLOG_NOTICE, 0, r, APLOGNO(02827)
                                  "err on client");
                    c->aborted = 1;
                    done = 1;
