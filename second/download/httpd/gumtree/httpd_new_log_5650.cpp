ap_log_cerror(APLOG_MARK, APLOG_ERR, rv, c, APLOGNO(01974)
                      "could not connect to %s '%s'",
                      proxy_uri ? "proxy" : "OCSP responder",
                      next_hop_uri->hostinfo);