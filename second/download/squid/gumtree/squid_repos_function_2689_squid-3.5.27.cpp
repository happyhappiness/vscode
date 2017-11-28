void
htcpSpecifier::checkHit()
{
    char *blk_end;
    checkHitRequest = request;

    if (NULL == checkHitRequest) {
        debugs(31, 3, "htcpCheckHit: NO; failed to parse URL");
        checkedHit(NullStoreEntry::getInstance());
        return;
    }

    blk_end = req_hdrs + strlen(req_hdrs);

    if (!checkHitRequest->header.parse(req_hdrs, blk_end)) {
        debugs(31, 3, "htcpCheckHit: NO; failed to parse request headers");
        delete checkHitRequest;
        checkHitRequest = NULL;
        checkedHit(NullStoreEntry::getInstance());
        return;
    }

    StoreEntry::getPublicByRequest(this, checkHitRequest);
}