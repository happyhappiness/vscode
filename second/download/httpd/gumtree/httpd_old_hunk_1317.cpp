        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't unlink unix domain socket %s",
                     sconf->sockname);
        /* just a warning; don't bail out */
    }

    if ((sd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server, 
                     "Couldn't create unix domain socket");
        return errno;
    } 

