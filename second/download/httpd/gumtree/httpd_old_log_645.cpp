ap_log_error(APLOG_MARK, APLOG_ERR|APLOG_NOERRNO, 0, NULL,
                         "Cannot remove module %s: not found in module list",
                         m->name);