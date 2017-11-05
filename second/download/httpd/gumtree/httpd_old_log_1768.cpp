ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                             "proxy: ProxyBlock comparing %s and %s", conf_ip, uri_ip);