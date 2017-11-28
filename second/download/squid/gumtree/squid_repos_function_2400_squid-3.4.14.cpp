void
store_client::callback(ssize_t sz, bool error)
{
    StoreIOBuffer result(sz, 0 ,copyInto.data);

    if (sz < 0) {
        result.flags.error = 1;
        result.length = 0;
    } else {
        result.flags.error = error ? 1 : 0;
    }

    result.offset = cmp_offset;
    assert(_callback.pending());
    cmp_offset = copyInto.offset + sz;
    STCB *temphandler = _callback.callback_handler;
    void *cbdata = _callback.callback_data;
    _callback = Callback(NULL, NULL);
    copyInto.data = NULL;

    if (cbdataReferenceValid(cbdata))
        temphandler(cbdata, result);

    cbdataReferenceDone(cbdata);
}