void
htcpSpecifier::created(StoreEntry *e)
{
    StoreEntry *hit = nullptr;

    if (!e || e->isNull()) {
        debugs(31, 3, "htcpCheckHit: NO; public object not found");
    } else if (!e->validToSend()) {
        debugs(31, 3, "htcpCheckHit: NO; entry not valid to send" );
    } else if (refreshCheckHTCP(e, checkHitRequest.getRaw())) {
        debugs(31, 3, "htcpCheckHit: NO; cached response is stale");
    } else {
        debugs(31, 3, "htcpCheckHit: YES!?");
        hit = e;
    }

    checkedHit(hit);
}