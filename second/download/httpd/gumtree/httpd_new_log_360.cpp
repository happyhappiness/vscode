ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_EMERG, NULL,
                 "dyld found undefined symbol: %s\n"
                 "Aborting.\n",
                 symbolName);