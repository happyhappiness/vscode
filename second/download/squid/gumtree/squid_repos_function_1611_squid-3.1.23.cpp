void
httpHdrScUpdateStats(const HttpHdrSc * sc, StatHist * hist)
{
    dlink_node *sct;
    assert(sc);
    sct = sc->targets.head;

    while (sct) {
        httpHdrScTargetUpdateStats((HttpHdrScTarget *)sct->data, hist);
        sct = sct->next;
    }
}