ap_log_error(APLOG_MARK, APLOG_WARNING | APLOG_NOERRNO, 0, s,
                     "WARNING: Attempt to change ServerLimit or ThreadLimit "
                     "ignored during restart");