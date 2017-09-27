ap_log_error(APLOG_MARK, APLOG_WARNING, 0, ap_server_conf, APLOGNO(02176)
                         "new file descriptor %d is too large; you probably need "
                         "to rebuild Apache with a larger FD_SETSIZE "
                         "(currently %d)",
                         sockdes, FD_SETSIZE);