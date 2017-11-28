#endif

        storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
                          (long int) http->start_time.tv_sec,
                          (int) http->start_time.tv_usec,
                          tvSubDsec(http->start_time, current_time));
#if USE_AUTH
        if (http->request->auth_user_request != NULL)
            p = http->request->auth_user_request->username();
        else
#endif
            if (http->request->extacl_user.defined()) {
                p = http->request->extacl_user.termedBuf();
            }

        if (!p && conn != NULL && conn->clientConnection->rfc931[0])
            p = conn->clientConnection->rfc931;

#if USE_SSL

        if (!p && conn != NULL && Comm::IsConnOpen(conn->clientConnection))
            p = sslGetUserEmail(fd_table[conn->clientConnection->fd].ssl);

#endif

        if (!p)
            p = dash_str;

        storeAppendPrintf(s, "username %s\n", p);

#if USE_DELAY_POOLS
        storeAppendPrintf(s, "delay_pool %d\n", DelayId::DelayClient(http).pool());
#endif

        storeAppendPrintf(s, "\n");
    }
}

