inline void clear() {
        type = 0;
        remote_port = 0;
        local_addr.SetEmpty();
        tosToServer = '\0';
        nfmarkToServer = 0;
        sock_family = 0;
        memset(ipaddr, '\0', MAX_IPSTRLEN);
        memset(desc,'\0',FD_DESC_SZ);
        memset(&flags,0,sizeof(_fde_flags));
        bytes_read = 0;
        bytes_written = 0;
        pconn.uses = 0;
        pconn.pool = NULL;
#if USE_DELAY_POOLS
        clientInfo = NULL;
#endif
        epoll_state = 0;
        read_handler = NULL;
        read_data = NULL;
        write_handler = NULL;
        write_data = NULL;
        timeoutHandler = NULL;
        timeout = 0;
        writeStart = 0;
        lifetime_data = NULL;
        closeHandler = NULL;
        halfClosedReader = NULL;
        wstate = NULL;
        read_method = NULL;
        write_method = NULL;
#if USE_SSL
        ssl = NULL;
        dynamicSslContext = NULL;
#endif
#if _SQUID_WINDOWS_
        win32.handle = NULL;
#endif
        tosFromServer = '\0';
        nfmarkFromServer = 0;
    }