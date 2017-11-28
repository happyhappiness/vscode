void
ACLChecklist::checkCallback(allow_t answer)
{
    ACLCB *callback_;
    void *cbdata_;
    debugs(28, 3, "ACLChecklist::checkCallback: " << this << " answer=" << answer);

    callback_ = callback;
    callback = NULL;

    if (cbdataReferenceValidDone(callback_data, &cbdata_))
        callback_(answer, cbdata_);

    // not really meaningful just before delete, but here for completeness sake
    occupied_ = false;

    delete this;
}