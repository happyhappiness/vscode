ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                     "ap_proxy_ajp_request: origin server "
                                     "sent 401 without WWW-Authenticate header");