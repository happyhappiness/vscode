ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                             "ProtocolEcho: Failure reading from %s",
                             c->remote_ip);