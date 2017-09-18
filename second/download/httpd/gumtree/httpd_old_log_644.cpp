ap_log_error(APLOG_MARK, APLOG_STARTUP | APLOG_NOERRNO, 0, NULL,
                         "module limit was reached. Please increase "
                         "DYNAMIC_MODULE_LIMIT and recompile.");