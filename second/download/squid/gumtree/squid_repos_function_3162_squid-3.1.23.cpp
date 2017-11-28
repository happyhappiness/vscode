void
gopherStart(FwdState * fwd)
{
    int fd = fwd->server_fd;
    StoreEntry *entry = fwd->entry;
    GopherStateData *gopherState;
    CBDATA_INIT_TYPE(GopherStateData);
    gopherState = cbdataAlloc(GopherStateData);
    gopherState->buf = (char *)memAllocate(MEM_4K_BUF);

    entry->lock();
    gopherState->entry = entry;

    gopherState->fwd = fwd;

    debugs(10, 3, "gopherStart: " << entry->url()  );

    statCounter.server.all.requests++;

    statCounter.server.other.requests++;

    /* Parse url. */
    gopher_request_parse(fwd->request,
                         &gopherState->type_id, gopherState->request);

    comm_add_close_handler(fd, gopherStateFree, gopherState);

    if (((gopherState->type_id == GOPHER_INDEX) || (gopherState->type_id == GOPHER_CSO))
            && (strchr(gopherState->request, '?') == NULL)) {
        /* Index URL without query word */
        /* We have to generate search page back to client. No need for connection */
        gopherMimeCreate(gopherState);

        if (gopherState->type_id == GOPHER_INDEX) {
            gopherState->conversion = gopher_ds::HTML_INDEX_PAGE;
        } else {
            if (gopherState->type_id == GOPHER_CSO) {
                gopherState->conversion = gopher_ds::HTML_CSO_PAGE;
            } else {
                gopherState->conversion = gopher_ds::HTML_INDEX_PAGE;
            }
        }

        gopherToHTML(gopherState, (char *) NULL, 0);
        fwd->complete();
        comm_close(fd);
        return;
    }

    gopherState->fd = fd;
    gopherState->fwd = fwd;
    gopherSendRequest(fd, gopherState);
    commSetTimeout(fd, Config.Timeout.read, gopherTimeout, gopherState);
}