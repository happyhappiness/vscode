void
Rock::SwapDir::anchorEntry(StoreEntry &e, const sfileno filen, const Ipc::StoreMapAnchor &anchor)
{
    const Ipc::StoreMapAnchor::Basics &basics = anchor.basics;

    e.swap_file_sz = basics.swap_file_sz;
    e.lastref = basics.lastref;
    e.timestamp = basics.timestamp;
    e.expires = basics.expires;
    e.lastModified(basics.lastmod);
    e.refcount = basics.refcount;
    e.flags = basics.flags;

    if (anchor.complete()) {
        e.store_status = STORE_OK;
        e.swap_status = SWAPOUT_DONE;
    } else {
        e.store_status = STORE_PENDING;
        e.swap_status = SWAPOUT_WRITING; // even though another worker writes?
    }

    e.ping_status = PING_NONE;

    EBIT_CLR(e.flags, RELEASE_REQUEST);
    e.clearPrivate();
    EBIT_SET(e.flags, ENTRY_VALIDATED);

    e.swap_dirn = index;
    e.swap_filen = filen;
}