ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
                     "Digest: WARNING: qop `auth-int' currently only works "
                     "correctly for responses with no entity");