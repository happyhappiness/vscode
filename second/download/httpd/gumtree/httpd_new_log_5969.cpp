ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03043)
                          "h2_alt_svc: announce %s for %s:%d", 
                          (secure? "secure" : "insecure"), 
                          r->hostname, (int)r->server->port);