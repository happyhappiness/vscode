static int
htcpClrStore(const htcpSpecifier * s)
{
    HttpRequest *request = s->request;
    char *blk_end;
    StoreEntry *e = NULL;
    int released = 0;

    if (request == NULL) {
        debugs(31, 3, "htcpClrStore: failed to parse URL");
        return -1;
    }

    /* Parse request headers */
    blk_end = s->req_hdrs + strlen(s->req_hdrs);

    if (!request->header.parse(s->req_hdrs, blk_end)) {
        debugs(31, 2, "htcpClrStore: failed to parse request headers");
        return -1;
    }

    /* Lookup matching entries. This matches both GET and HEAD */
    while ((e = storeGetPublicByRequest(request)) != NULL) {
        if (e != NULL) {
            htcpClrStoreEntry(e);
            ++released;
        }
    }

    if (released) {
        debugs(31, 4, "htcpClrStore: Cleared " << released << " matching entries");
        return 1;
    } else {
        debugs(31, 4, "htcpClrStore: No matching entry found");
        return 0;
    }
}