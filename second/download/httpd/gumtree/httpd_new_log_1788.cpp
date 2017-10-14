ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                         "ProtocolEcho: Error - read empty brigade from %s!",
                         c->remote_ip);