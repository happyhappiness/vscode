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
            storeAppendPrintf(s, "\tin: buf %p, offset %ld, size %ld\n",
                              conn->in.buf, (long int) conn->in.notYetUsed, (long int) conn->in.allocatedSize);
            storeAppendPrintf(s, "\tremote: %s\n",
                              conn->clientConnection->remote.ToURL(buf,MAX_IPSTRLEN));
            storeAppendPrintf(s, "\tlocal: %s\n",
                              conn->clientConnection->local.ToURL(buf,MAX_IPSTRLEN));
            storeAppendPrintf(s, "\tnrequests: %d\n",
                              conn->nrequests);
        }

        storeAppendPrintf(s, "uri %s\n", http->uri);
        storeAppendPrintf(s, "logType %s\n", Format::log_tags[http->logType]);
        storeAppendPrintf(s, "out.offset %ld, out.size %lu\n",
                          (long int) http->out.offset, (unsigned long int) http->out.size);
        storeAppendPrintf(s, "req_sz %ld\n", (long int) http->req_sz);
        e = http->storeEntry();
        storeAppendPrintf(s, "entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
#if 0
