bool
MemStore::copyFromShm(StoreEntry &e, const MemStoreMap::Extras &extras)
{
    const Ipc::Mem::PageId &page = extras.page;

    StoreIOBuffer sourceBuf(extras.storedSize, 0,
                            static_cast<char*>(PagePointer(page)));

    // XXX: We do not know the URLs yet, only the key, but we need to parse and
    // store the response for the Root().get() callers to be happy because they
    // expect IN_MEMORY entries to already have the response headers and body.
    // At least one caller calls createMemObject() if there is not one, so
    // we hide the true object until that happens (to avoid leaking TBD URLs).
    e.createMemObject("TBD", "TBD");

    // emulate the usual Store code but w/o inapplicable checks and callbacks:

    // from store_client::readBody():
    HttpReply *rep = (HttpReply *)e.getReply();
    const ssize_t end = headersEnd(sourceBuf.data, sourceBuf.length);
    if (!rep->parseCharBuf(sourceBuf.data, end)) {
        debugs(20, DBG_IMPORTANT, "Could not parse mem-cached headers: " << e);
        return false;
    }
    // local memory stores both headers and body
    e.mem_obj->object_sz = sourceBuf.length; // from StoreEntry::complete()

    storeGetMemSpace(sourceBuf.length); // from StoreEntry::write()

    assert(e.mem_obj->data_hdr.write(sourceBuf)); // from MemObject::write()
    const int64_t written = e.mem_obj->endOffset();
    // we should write all because StoreEntry::write() never fails
    assert(written >= 0 &&
           static_cast<size_t>(written) == sourceBuf.length);
    // would be nice to call validLength() here, but it needs e.key

    debugs(20, 7, HERE << "mem-loaded all " << written << " bytes of " << e <<
           " from " << page);

    e.hideMemObject();

    return true;
}