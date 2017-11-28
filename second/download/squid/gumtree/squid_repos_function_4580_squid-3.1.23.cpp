void
CossState::doCallback(int errflag)
{
    STIOCB *callback = this->callback;
    void *cbdata;
    debugs(79, 3, "CossState::doCallback: errflag=" << errflag);
    assert(NULL == locked_membuf);
    xfree(readbuffer);
    this->callback = NULL;

    if (cbdataReferenceValidDone(callback_data, &cbdata))
        callback(cbdata, errflag, this);
}