ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                     "new file descriptor %d is too large; you probably need "
                     "to rebuild Apache with a larger FD_SETSIZE "
                     "(currently %d)", 
                     csd, FD_SETSIZE);