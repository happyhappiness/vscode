static void
statClientRequests(StoreEntry * s)
{
    dlink_node *i;
    ClientHttpRequest *http;
    StoreEntry *e;
    int fd;
    char buf[MAX_IPSTRLEN];

    for (i = ClientActiveRequests.head; i; i = i->next) {
        const char *p = NULL;
        http = static_cast<ClientHttpRequest *>(i->data);
        assert(http);
        ConnStateData * conn = http->getConn();
        storeAppendPrintf(s, "Connection: %p\n", conn);

        if (conn != NULL) {
            fd = conn->fd;
            storeAppendPrintf(s, "\tFD %d, read %" PRId64 ", wrote %" PRId64 "\n", fd,
                              fd_table[fd].bytes_read, fd_table[fd].bytes_written);
            storeAppendPrintf(s, "\tFD desc: %s\n", fd_table[fd].desc);
            storeAppendPrintf(s, "\tin: buf %p, offset %ld, size %ld\n",
                              conn->in.buf, (long int) conn->in.notYetUsed, (long int) conn->in.allocatedSize);
            storeAppendPrintf(s, "\tpeer: %s:%d\n",
                              conn->peer.NtoA(buf,MAX_IPSTRLEN),
                              conn->peer.GetPort());
            storeAppendPrintf(s, "\tme: %s:%d\n",
                              conn->me.NtoA(buf,MAX_IPSTRLEN),
                              conn->me.GetPort());
            storeAppendPrintf(s, "\tnrequests: %d\n",
                              conn->nrequests);
        }

        storeAppendPrintf(s, "uri %s\n", http->uri);
        storeAppendPrintf(s, "logType %s\n", log_tags[http->logType]);
        storeAppendPrintf(s, "out.offset %ld, out.size %lu\n",
                          (long int) http->out.offset, (unsigned long int) http->out.size);
        storeAppendPrintf(s, "req_sz %ld\n", (long int) http->req_sz);
        e = http->storeEntry();
        storeAppendPrintf(s, "entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
#if 0
        /* Not a member anymore */
        e = http->old_entry;
        storeAppendPrintf(s, "old_entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
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