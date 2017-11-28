void
store_client::unpackHeader(char const *buf, ssize_t len)
{
    debugs(90, 3, "store_client::unpackHeader: len " << len << "");

    if (len < 0) {
        debugs(90, 3, "store_client::unpackHeader: " << xstrerror() << "");
        fail();
        return;
    }

    int swap_hdr_sz = 0;
    StoreMetaUnpacker aBuilder(buf, len, &swap_hdr_sz);

    if (!aBuilder.isBufferSane()) {
        /* oops, bad disk file? */
        debugs(90, 1, "WARNING: swapfile header inconsistent with available data");
        fail();
        return;
    }

    tlv *tlv_list = aBuilder.createStoreMeta ();

    if (tlv_list == NULL) {
        debugs(90, 1, "WARNING: failed to unpack meta data");
        fail();
        return;
    }

    /*
     * Check the meta data and make sure we got the right object.
     */
    for (tlv *t = tlv_list; t; t = t->next) {
        if (!t->checkConsistency(entry)) {
            storeSwapTLVFree(tlv_list);
            fail();
            return;
        }
    }

    storeSwapTLVFree(tlv_list);

    entry->mem_obj->swap_hdr_sz = swap_hdr_sz;
    entry->mem_obj->object_sz = entry->swap_file_sz - swap_hdr_sz;

}