        }
    }
    while ((backend_addr || conn->uds_path) && !connected) {
#if APR_HAVE_SYS_UN_H
        if (conn->uds_path)
        {
            rv = apr_socket_create(&newsock, AF_UNIX, SOCK_STREAM, 0,
                                   conn->scpool);
            if (rv != APR_SUCCESS) {
                loglevel = APLOG_ERR;
                ap_log_error(APLOG_MARK, loglevel, rv, s, APLOGNO(02453)
                             "%s: error creating Unix domain socket for "
