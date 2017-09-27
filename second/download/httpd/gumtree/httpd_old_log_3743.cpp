ap_log_error(APLOG_MARK, APLOG_INFO, rv, c->base_server,
                         "ProtocolEcho: Failure writing to %s",
                         c->remote_ip);