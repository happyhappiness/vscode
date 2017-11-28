bool
store_client::unpackHeader(char const *buf, ssize_t len)
{
    debugs(90, 3, "store_client::unpackHeader: len " << len << "");

    if (len < 0) {
        debugs(90, 3, "WARNING: unpack error: " << xstrerror());
        return false;
    }

    int swap_hdr_sz = 0;
    StoreMetaUnpacker aBuilder(buf, len, &swap_hdr_sz);

    if (!aBuilder.isBufferSane()) {
        /* oops, bad disk file? */
        debugs(90, DBG_IMPORTANT, "WARNING: swapfile header inconsistent with available data");
        return false;
    }

    tlv *tlv_list = aBuilder.createStoreMeta ();

    if (tlv_list == NULL) {
        debugs(90, DBG_IMPORTANT, "WARNING: failed to unpack meta data");
        return false;
    }

    /*
     * Check the meta data and make sure we got the right object.
     */
    for (tlv *t = tlv_list; t; t = t->next) {
        if (!t->checkConsistency(entry)) {
            storeSwapTLVFree(tlv_list);
            return false;
        }
    }

    storeSwapTLVFree(tlv_list);

    assert(swap_hdr_sz >= 0);
    entry->mem_obj->swap_hdr_sz = swap_hdr_sz;
    if (entry->swap_file_sz > 0) { // collapsed hits may not know swap_file_sz
        assert(entry->swap_file_sz >= static_cast<uint64_t>(swap_hdr_sz));
        entry->mem_obj->object_sz = entry->swap_file_sz - swap_hdr_sz;
    }
    debugs(90, 5, "store_client::unpackHeader: swap_file_sz=" <<
           entry->swap_file_sz << "( " << swap_hdr_sz << " + " <<
           entry->mem_obj->object_sz << ")");
    return true;
}