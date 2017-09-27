ap_log_perror(APLOG_MARK, APLOG_NOTICE, rv, ptemp,
                      "mod_privileges: unable to determine MPM characteristics."
                      "  Please ensure you are using a non-threaded MPM "
                      "with this module.");