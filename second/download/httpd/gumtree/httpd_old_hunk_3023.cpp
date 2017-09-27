    }
    else {
        user = "anonymous";
        password = "apache-proxy@";
    }

    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
       "proxy: FTP: connecting %s to %s:%d", url, connectname, connectport);

    if (worker->is_address_reusable) {
        if (!worker->cp->addr) {
            if ((err = PROXY_THREAD_LOCK(worker)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_ERR, err, r->server,
                             "proxy: FTP: lock");
                return HTTP_INTERNAL_SERVER_ERROR;
            }
        }
        connect_addr = worker->cp->addr;
        address_pool = worker->cp->pool;
    }
