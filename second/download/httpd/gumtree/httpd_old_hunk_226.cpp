        else
#endif
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    apr_sockaddr_ip_get(&ipaddrstr, sockaddr);
    ap_log_error(APLOG_MARK, APLOG_NOERRNO|APLOG_INFO, 0, main_server,
                "mod_unique_id: using ip addr %s",
                 ipaddrstr);

    /*
     * If the server is pummelled with restart requests we could possibly end
     * up in a situation where we're starting again during the same second
