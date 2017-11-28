void
store_client::readHeader(char const *buf, ssize_t len)
{
    MemObject *const mem = entry->mem_obj;

    assert(flags.disk_io_pending);
    flags.disk_io_pending = false;
    assert(_callback.pending());

    // abort if we fail()'d earlier
    if (!object_ok)
        return;

    if (!unpackHeader(buf, len)) {
        fail();
        return;
    }

    /*
     * If our last read got some data the client wants, then give
     * it to them, otherwise schedule another read.
     */
    size_t body_sz = len - mem->swap_hdr_sz;

    if (copyInto.offset < static_cast<int64_t>(body_sz)) {
        /*
         * we have (part of) what they want
         */
        size_t copy_sz = min(copyInto.length, body_sz);
        debugs(90, 3, "storeClientReadHeader: copying " << copy_sz << " bytes of body");
        memmove(copyInto.data, copyInto.data + mem->swap_hdr_sz, copy_sz);

        readBody(copyInto.data, copy_sz);

        return;
    }

    /*
     * we don't have what the client wants, but at least we now
     * know the swap header size.
     */
    fileRead();
}