void
Rock::IoState::callReaderBack(const char *buf, int rlen)
{
    debugs(79, 5, rlen << " bytes for " << *e);
    splicingPoint = rlen >= 0 ? sidCurrent : -1;
    if (splicingPoint < 0)
        staleSplicingPointNext = -1;
    else
        staleSplicingPointNext = currentReadableSlice().next;
    StoreIOState::STRCB *callb = read.callback;
    assert(callb);
    read.callback = NULL;
    void *cbdata;
    if (cbdataReferenceValidDone(read.callback_data, &cbdata))
        callb(cbdata, buf, rlen, this);
}