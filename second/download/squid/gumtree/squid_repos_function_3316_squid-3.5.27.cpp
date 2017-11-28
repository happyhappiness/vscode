void
gopherStart(FwdState * fwd)
{
    StoreEntry *entry = fwd->entry;
    GopherStateData *gopherState;
    CBDATA_INIT_TYPE(GopherStateData);
    gopherState = cbdataAlloc(GopherStateData);
    gopherState->buf = (char *)memAllocate(MEM_4K_BUF);

    entry->lock("gopherState");
    gopherState->entry = entry;

    gopherState->fwd = fwd;

    debugs(10, 3, "gopherStart: " << entry->url()  );

    ++ statCounter.server.all.requests;

    ++ statCounter.server.other.requests;

    /* Parse url. */
    gopher_request_parse(fwd->request,
                         &gopherState->type_id, gopherState->request);

    comm_add_close_handler(fwd->serverConnection()->fd, gopherStateFree, gopherState);

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
        return;
    }

    gopherState->serverConn = fwd->serverConnection();
    gopherSendRequest(fwd->serverConnection()->fd, gopherState);
    AsyncCall::Pointer timeoutCall = commCbCall(5, 4, "gopherTimeout",
                                     CommTimeoutCbPtrFun(gopherTimeout, gopherState));
    commSetConnTimeout(fwd->serverConnection(), Config.Timeout.read, timeoutCall);
}