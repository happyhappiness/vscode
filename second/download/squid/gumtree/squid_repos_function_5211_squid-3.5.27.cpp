void
Rock::IoState::callReaderBack(const char *buf, int rlen)
{
    debugs(79, 5, rlen << " bytes for " << *e);
    StoreIOState::STRCB *callb = read.callback;
    assert(callb);
    read.callback = NULL;
    void *cbdata;
    if (cbdataReferenceValidDone(read.callback_data, &cbdata))
        callb(cbdata, buf, rlen, this);
}