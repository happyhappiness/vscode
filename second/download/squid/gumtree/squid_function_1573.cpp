static void
statClientRequests(StoreEntry * s)
{
    dlink_node *i;
    ClientHttpRequest *http;
    StoreEntry *e;
    char buf[MAX_IPSTRLEN];

    for (i = ClientActiveRequests.head; i; i = i->next) {
        const char *p = NULL;
        http = static_cast<ClientHttpRequest *>(i->data);
        assert(http);
        ConnStateData * conn = http->getConn();
        storeAppendPrintf(s, "Connection: %p\n", conn);

        if (conn != NULL) {
            const int fd = conn->clientConnection->fd;
            storeAppendPrintf(s, "\tFD %d, read %" PRId64 ", wrote %" PRId64 "\n", fd,
                              fd_table[fd].bytes_read, fd_table[fd].bytes_written);
            storeAppendPrintf(s, "\tFD desc: %s\n", fd_table[fd].desc);
            storeAppendPrintf(s, "\tin: buf %p, used %ld, free %ld\n",
                              conn->in.buf.c_str(), (long int) conn->in.buf.length(), (long int) conn->in.buf.spaceSize());
            storeAppendPrintf(s, "\tremote: %s\n",
                              conn->clientConnection->remote.toUrl(buf,MAX_IPSTRLEN));
            storeAppendPrintf(s, "\tlocal: %s\n",
                              conn->clientConnection->local.toUrl(buf,MAX_IPSTRLEN));
            storeAppendPrintf(s, "\tnrequests: %d\n",
                              conn->nrequests);
        }

        storeAppendPrintf(s, "uri %s\n", http->uri);
        storeAppendPrintf(s, "logType %s\n", LogTags_str[http->logType]);
        storeAppendPrintf(s, "out.offset %ld, out.size %lu\n",
                          (long int) http->out.offset, (unsigned long int) http->out.size);
        storeAppendPrintf(s, "req_sz %ld\n", (long int) http->req_sz);
        e = http->storeEntry();
        storeAppendPrintf(s, "entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
        storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
                          (long int) http->al->cache.start_time.tv_sec,
                          (int) http->al->cache.start_time.tv_usec,
                          tvSubDsec(http->al->cache.start_time, current_time));
#if USE_AUTH
        if (http->request->auth_user_request != NULL)
            p = http->request->auth_user_request->username();
        else
#endif
            if (http->request->extacl_user.size() > 0) {
                p = http->request->extacl_user.termedBuf();
            }

        if (!p && conn != NULL && conn->clientConnection->rfc931[0])
            p = conn->clientConnection->rfc931;

#if USE_OPENSSL

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