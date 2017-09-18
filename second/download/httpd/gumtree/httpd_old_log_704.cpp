ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_WARNING, 0, NULL,
                     "filedescriptor (%u) larger than FD_SETSIZE (%u) "
                     "found, you probably need to rebuild Apache with a "
                     "larger FD_SETSIZE", csd, FD_SETSIZE);