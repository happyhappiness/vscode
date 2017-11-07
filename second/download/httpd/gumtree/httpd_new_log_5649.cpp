ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(01973)
                  "connecting to %s '%s'",
                  proxy_uri ? "proxy" : "OCSP responder",
                  uri->hostinfo);