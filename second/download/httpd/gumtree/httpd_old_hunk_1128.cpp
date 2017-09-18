    opts.sidtimeout = 0;
    opts.sidentries = 0;
    opts.siddir = NULL;

    if (WSAIoctl(s, SO_SSL_SET_SERVER, (char *)&opts, sizeof(opts),
        NULL, 0, NULL, NULL, NULL) != 0) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
                     "make_secure_socket: for %s, WSAIoctl: "
                     "(SO_SSL_SET_SERVER)", addr);
        return -1;
    }

    if (mutual) {
        optParam = 0x07;  // SO_SSL_AUTH_CLIENT

        if(WSAIoctl(s, SO_SSL_SET_FLAGS, (char*)&optParam,
            sizeof(optParam), NULL, 0, NULL, NULL, NULL)) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, apr_get_netos_error(), sconf,
                         "make_secure_socket: for %s, WSAIoctl: "
                         "(SO_SSL_SET_FLAGS)", addr);
            return -1;
        }
    }

