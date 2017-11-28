void
CossSwapDir::readCompleted(const char *buf, int len, int errflag, RefCount<ReadRequest> aRequest)
{
    CossRead* cossRead= dynamic_cast<CossRead *>(aRequest.getRaw());
    assert (cossRead);
    StoreIOState::Pointer sio =  cossRead->sio;
    void *cbdata;
    StoreIOState::STRCB *callback = sio->read.callback;
    char *p;
    CossState *cstate = dynamic_cast<CossState *>(sio.getRaw());
    ssize_t rlen;

    debugs(79, 3, "storeCossReadDone: fileno " << sio->swap_filen << ", len " << len);
    cstate->flags.reading = 0;

    if (errflag) {
        StoreFScoss::GetInstance().stats.read.fail++;

        if (errflag > 0) {
            errno = errflag;
            debugs(79, 1, "storeCossReadDone: error: " << xstrerror());
        } else {
            debugs(79, 1, "storeCossReadDone: got failure (" << errflag << ")");
        }

        rlen = -1;
    } else {
        StoreFScoss::GetInstance().stats.read.success++;

        if (cstate->readbuffer == NULL) {
            cstate->readbuffer = (char *)xmalloc(cstate->st_size);
            p = storeCossMemPointerFromDiskOffset(storeCossFilenoToDiskOffset(sio->swap_filen),
                                                  NULL);
            xmemcpy(cstate->readbuffer, p, cstate->st_size);
        }

        sio->offset_ += len;
        xmemcpy(cstate->requestbuf, &cstate->readbuffer[cstate->requestoffset],
                cstate->requestlen);
        rlen = (size_t) cstate->requestlen;
    }

    assert(callback);
    sio->read.callback = NULL;

    if (cbdataReferenceValidDone(sio->read.callback_data, &cbdata))
        callback(cbdata, cstate->requestbuf, rlen, sio);
}