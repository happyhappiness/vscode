{
    StoreEntry *sentry = (StoreEntry *)_sentry;
    rtentry_t *e = (rtentry_t *) rn;
    CbDataList<int> *q;
    as_info *asinfo;
    char buf[MAX_IPSTRLEN];
    Ip::Address addr;
    Ip::Address mask;

    assert(e);
    assert(e->e_info);
    addr = e->e_addr.addr;
    mask = e->e_mask.addr;
    storeAppendPrintf(sentry, "%s/%d\t",
