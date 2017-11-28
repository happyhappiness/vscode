void
store_client::copy(StoreEntry * anEntry,
                   StoreIOBuffer copyRequest,
                   STCB * callback_fn,
                   void *data)
{
    assert (anEntry == entry);
    assert (callback_fn);
    assert (data);
    assert(!EBIT_TEST(entry->flags, ENTRY_ABORTED));
    debugs(90, 3, "store_client::copy: " << entry->getMD5Text() << ", from " <<
           copyRequest.offset << ", for length " <<
           (int) copyRequest.length << ", cb " << callback_fn << ", cbdata " <<
           data);

#if STORE_CLIENT_LIST_DEBUG

    assert(this == storeClientListSearch(entry->mem_obj, data));
#endif

    assert(!_callback.pending());
#if ONLYCONTIGUOUSREQUESTS

    assert(cmp_offset == copyRequest.offset);
#endif
    /* range requests will skip into the body */
    cmp_offset = copyRequest.offset;
    _callback = Callback (callback_fn, cbdataReference(data));
    copyInto.data = copyRequest.data;
    copyInto.length = copyRequest.length;
    copyInto.offset = copyRequest.offset;

    static bool copying (false);
    assert (!copying);
    copying = true;
    PROF_start(storeClient_kickReads);
    /* we might be blocking comm reads due to readahead limits
     * now we have a new offset, trigger those reads...
     */
    entry->mem_obj->kickReads();
    PROF_stop(storeClient_kickReads);
    copying = false;

    // XXX: storeClientCopy2 calls doCopy() whose callback may free 'this'!
    // We should make store copying asynchronous, to avoid worrying about
    // 'this' being secretly deleted while we are still inside the object.
    // For now, lock and use on-stack objects after storeClientCopy2().
    ++anEntry->lock_count;

    storeClientCopy2(entry, this);

#if USE_ADAPTATION
    anEntry->kickProducer();
#endif

    anEntry->unlock(); // after the "++enEntry->lock_count" above
    // Add no code here. This object may no longer exist.
}