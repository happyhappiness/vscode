ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_DEBUG, NULL,
                 "dyld found a multiply defined symbol %s in modules:\n"
                 "%s\n%s\n",
                 NSNameOfSymbol(s),
                 NSNameOfModule(old), NSNameOfModule(new));