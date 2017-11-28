void
ACLChecklist::checkCallback(allow_t answer)
{
    PF *callback_;
    void *cbdata_;
    debugs(28, 3, "ACLChecklist::checkCallback: " << this << " answer=" << answer);

    callback_ = callback;
    callback = NULL;

    if (cbdataReferenceValidDone(callback_data, &cbdata_))
        callback_(answer, cbdata_);

    delete this;
}