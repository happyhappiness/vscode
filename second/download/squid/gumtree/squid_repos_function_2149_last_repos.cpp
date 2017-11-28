void
htcpSpecifier::checkHit()
{
    checkHitRequest = request;

    if (!checkHitRequest) {
        debugs(31, 3, "htcpCheckHit: NO; failed to parse URL");
        checkedHit(NullStoreEntry::getInstance());
        return;
    }

    if (!checkHitRequest->header.parse(req_hdrs, reqHdrsSz)) {
        debugs(31, 3, "htcpCheckHit: NO; failed to parse request headers");
        checkHitRequest = nullptr;
        checkedHit(NullStoreEntry::getInstance());
        return;
    }

    StoreEntry::getPublicByRequest(this, checkHitRequest.getRaw());
}