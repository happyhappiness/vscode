void
store_client::readHeader(char const *buf, ssize_t len)
{
    MemObject *const mem = entry->mem_obj;

    assert(flags.disk_io_pending);
    flags.disk_io_pending = 0;
    assert(_callback.pending());

    unpackHeader (buf, len);

    if (!object_ok)
        return;

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
        xmemmove(copyInto.data, copyInto.data + mem->swap_hdr_sz, copy_sz);

        if (copyInto.offset == 0 && len > 0 && entry->getReply()->sline.status == 0) {
            /* Our structure ! */
            HttpReply *rep = (HttpReply *) entry->getReply(); // bypass const

            if (!rep->parseCharBuf(copyInto.data, headersEnd(copyInto.data, copy_sz))) {
                debugs(90, 0, "could not parse headers from on disk structure!");
            }
        }

        callback(copy_sz);
        return;
    }

    /*
     * we don't have what the client wants, but at least we now
     * know the swap header size.
     */
    fileRead();
}