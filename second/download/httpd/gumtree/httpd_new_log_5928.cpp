ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(03355)
                              "access check for %s as '%s': %s",
                              r->useragent_ip, w, match? "yes": "no");