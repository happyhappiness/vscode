ap_log_error(APLOG_MARK, APLOG_NOERRNO | APLOG_WARNING, 0, NULL,
                     "macro '%s' (%s): empty contents!",
                     macro->name, macro->location);