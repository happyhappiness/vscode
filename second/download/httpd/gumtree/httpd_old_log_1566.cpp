ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
                "Oops, no RSA or DSA server certificate found "
                "for '%s:%d'?!", s->server_hostname, s->port);