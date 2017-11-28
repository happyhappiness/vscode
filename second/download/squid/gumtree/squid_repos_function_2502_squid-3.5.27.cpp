void
store_client::readBody(const char *buf, ssize_t len)
{
    int parsed_header = 0;

    // Don't assert disk_io_pending here.. may be called by read_header
    flags.disk_io_pending = false;
    assert(_callback.pending());
    debugs(90, 3, "storeClientReadBody: len " << len << "");

    if (copyInto.offset == 0 && len > 0 && entry->getReply()->sline.status() == Http::scNone) {
        /* Our structure ! */
        HttpReply *rep = (HttpReply *) entry->getReply(); // bypass const

        if (!rep->parseCharBuf(copyInto.data, headersEnd(copyInto.data, len))) {
            debugs(90, DBG_CRITICAL, "Could not parse headers from on disk object");
        } else {
            parsed_header = 1;
        }
    }

    const HttpReply *rep = entry->getReply();
    if (len > 0 && rep && entry->mem_obj->inmem_lo == 0 && entry->objectLen() <= (int64_t)Config.Store.maxInMemObjSize && Config.onoff.memory_cache_disk) {
        storeGetMemSpace(len);
        // The above may start to free our object so we need to check again
        if (entry->mem_obj->inmem_lo == 0) {
            /* Copy read data back into memory.
             * copyInto.offset includes headers, which is what mem cache needs
             */
            int64_t mem_offset = entry->mem_obj->endOffset();
            if ((copyInto.offset == mem_offset) || (parsed_header && mem_offset == rep->hdr_sz)) {
                entry->mem_obj->write(StoreIOBuffer(len, copyInto.offset, copyInto.data));
            }
        }
    }

    callback(len);
}