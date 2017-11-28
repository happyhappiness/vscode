void
UrnState::created(StoreEntry *newEntry)
{
    urlres_e = newEntry;

    if (urlres_e->isNull()) {
        urlres_e = storeCreateEntry(urlres, urlres, request_flags(), METHOD_GET);
        sc = storeClientListAdd(urlres_e, this);
        FwdState::fwdStart(-1, urlres_e, urlres_r);
    } else {

        urlres_e->lock();
        sc = storeClientListAdd(urlres_e, this);
    }

    reqofs = 0;
    StoreIOBuffer tempBuffer;
    tempBuffer.offset = reqofs;
    tempBuffer.length = URN_REQBUF_SZ;
    tempBuffer.data = reqbuf;
    storeClientCopy(sc, urlres_e,
                    tempBuffer,
                    urnHandleReply,
                    this);
}