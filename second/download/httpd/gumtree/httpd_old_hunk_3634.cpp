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
