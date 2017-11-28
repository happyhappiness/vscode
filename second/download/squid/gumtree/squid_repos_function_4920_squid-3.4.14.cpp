void
Rock::SwapDir::readCompleted(const char *buf, int rlen, int errflag, RefCount< ::ReadRequest> r)
{
    ReadRequest *request = dynamic_cast<Rock::ReadRequest*>(r.getRaw());
    assert(request);
    IoState::Pointer sio = request->sio;

    if (errflag == DISK_OK && rlen > 0)
        sio->offset_ += rlen;
    assert(sio->diskOffset + sio->offset_ <= diskOffsetLimit()); // post-factum

    StoreIOState::STRCB *callb = sio->read.callback;
    assert(callb);
    sio->read.callback = NULL;
    void *cbdata;
    if (cbdataReferenceValidDone(sio->read.callback_data, &cbdata))
        callb(cbdata, r->buf, rlen, sio.getRaw());
}