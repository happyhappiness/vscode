ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0,
                         cmd->server, "Digest: WARNING: algorithm `MD5-sess' "
                         "is not supported on platforms without shared-memory "
                         "support - reverting to MD5");