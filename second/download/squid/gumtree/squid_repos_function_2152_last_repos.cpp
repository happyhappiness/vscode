static int
htcpClrStore(const htcpSpecifier::Pointer &s)
{
    HttpRequestPointer request(s->request);
    if (!request) {
        debugs(31, 3, "htcpClrStore: failed to parse URL");
        return -1;
    }

    /* Parse request headers */
    if (!request->header.parse(s->req_hdrs, s->reqHdrsSz)) {
        debugs(31, 2, "htcpClrStore: failed to parse request headers");
        return -1;
    }

    StoreEntry *e = nullptr;
    int released = 0;
    /* Lookup matching entries. This matches both GET and HEAD */
    while ((e = storeGetPublicByRequest(request.getRaw()))) {
        htcpClrStoreEntry(e);
        ++released;
    }

    if (released) {
        debugs(31, 4, "htcpClrStore: Cleared " << released << " matching entries");
        return 1;
    } else {
        debugs(31, 4, "htcpClrStore: No matching entry found");
        return 0;
    }
}