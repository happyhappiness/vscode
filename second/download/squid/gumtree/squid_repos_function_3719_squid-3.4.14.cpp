void
UrnState::created(StoreEntry *newEntry)
{
    urlres_e = newEntry;

    if (urlres_e->isNull()) {
        urlres_e = storeCreateEntry(urlres, urlres, RequestFlags(), Http::METHOD_GET);
        sc = storeClientListAdd(urlres_e, this);
        FwdState::fwdStart(Comm::ConnectionPointer(), urlres_e, urlres_r.getRaw());
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