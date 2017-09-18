ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0,
                     cmd->server, "Digest: WARNING: nonce-count checking "
                     "is not supported on platforms without shared-memory "
                     "support - disabling check");