void
MemStore::anchorEntry(StoreEntry &e, const sfileno index, const Ipc::StoreMapAnchor &anchor)
{
    const Ipc::StoreMapAnchor::Basics &basics = anchor.basics;

    e.swap_file_sz = basics.swap_file_sz;
    e.lastref = basics.lastref;
    e.timestamp = basics.timestamp;
    e.expires = basics.expires;
    e.lastModified(basics.lastmod);
    e.refcount = basics.refcount;
    e.flags = basics.flags;

    assert(e.mem_obj);
    if (anchor.complete()) {
        e.store_status = STORE_OK;
        e.mem_obj->object_sz = e.swap_file_sz;
        e.setMemStatus(IN_MEMORY);
    } else {
        e.store_status = STORE_PENDING;
        assert(e.mem_obj->object_sz < 0);
        e.setMemStatus(NOT_IN_MEMORY);
    }
    assert(e.swap_status == SWAPOUT_NONE); // set in StoreEntry constructor
    e.ping_status = PING_NONE;

    EBIT_CLR(e.flags, RELEASE_REQUEST);
    e.clearPrivate();
    EBIT_SET(e.flags, ENTRY_VALIDATED);

    MemObject::MemCache &mc = e.mem_obj->memCache;
    mc.index = index;
    mc.io = MemObject::ioReading;
}