void
store_client::callback(ssize_t sz, bool error)
{
    size_t bSz = 0;

    if (sz >= 0 && !error)
        bSz = sz;

    StoreIOBuffer result(bSz, 0 ,copyInto.data);

    if (sz < 0 || error)
        result.flags.error = 1;

    result.offset = cmp_offset;
    assert(_callback.pending());
    cmp_offset = copyInto.offset + bSz;
    STCB *temphandler = _callback.callback_handler;
    void *cbdata = _callback.callback_data;
    _callback = Callback(NULL, NULL);
    copyInto.data = NULL;

    if (cbdataReferenceValid(cbdata))
        temphandler(cbdata, result);

    cbdataReferenceDone(cbdata);
}