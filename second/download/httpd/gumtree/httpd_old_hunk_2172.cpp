        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't bind unix domain socket %s",
                     sockname);
        return errno;
    }

    if (listen(sd, DEFAULT_CGID_LISTENBACKLOG) < 0) {
        ap_log_error(APLOG_MARK, APLOG_ERR, errno, main_server,
                     "Couldn't listen on unix domain socket");
        return errno;
    }

