ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, r->server,
                    "unknown parameter \"%s\" to tag %s in %s",
                    tag, directive, r->filename);