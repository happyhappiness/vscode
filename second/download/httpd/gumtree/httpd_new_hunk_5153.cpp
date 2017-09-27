        }
        else {
            lua_pushboolean(L, 0);
        }
        if (plen > 0) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, 
                        "Websocket: Reading %" APR_SIZE_T_FMT " bytes of PONG", plen);
            return 1;
        }
        if (mask) {
            plen = 2;
            apr_socket_recv(sock, prelude, &plen);
            plen = 2;
