#endif

        storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
                          (long int) http->start_time.tv_sec,
                          (int) http->start_time.tv_usec,
                          tvSubDsec(http->start_time, current_time));

        if (http->request->auth_user_request)
            p = http->request->auth_user_request->username();
        else if (http->request->extacl_user.defined()) {
            p = http->request->extacl_user.termedBuf();
        }

        if (!p && (conn != NULL && conn->rfc931[0]))
            p = conn->rfc931;

#if USE_SSL

        if (!p && conn != NULL)
            p = sslGetUserEmail(fd_table[conn->fd].ssl);

#endif

        if (!p)
            p = dash_str;

        storeAppendPrintf(s, "username %s\n", p);

#if DELAY_POOLS

        storeAppendPrintf(s, "delay_pool %d\n", DelayId::DelayClient(http).pool());

#endif

        storeAppendPrintf(s, "\n");
    }
}

