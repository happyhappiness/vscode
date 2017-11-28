static void
gopherTimeout(int fd, void *data)
{
    GopherStateData *gopherState = (GopherStateData *)data;
    StoreEntry *entry = gopherState->entry;
    debugs(10, 4, "gopherTimeout: FD " << fd << ": '" << entry->url() << "'" );

    gopherState->fwd->fail(errorCon(ERR_READ_TIMEOUT, HTTP_GATEWAY_TIMEOUT, gopherState->fwd->request));

    comm_close(fd);
}