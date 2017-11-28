static void
storeIdHandleReply(void *data, const Helper::Reply &reply)
{
    RedirectStateData *r = static_cast<RedirectStateData *>(data);
    debugs(61, 5,"StoreId helper: reply=" << reply);

    // XXX: This function is now kept only to check for and display the garbage use-case
    // and to map the old helper response format(s) into new format result code and key=value pairs
    // it can be removed when the helpers are all updated to the normalized "OK/ERR kv-pairs" format
    void *cbdata;
    if (cbdataReferenceValidDone(r->data, &cbdata))
        r->handler(cbdata, reply);

    delete r;
}