bool
store_client::unpackHeader(char const *buf, ssize_t len)
{
    int xerrno = errno; // FIXME: where does errno come from?
    debugs(90, 3, "store_client::unpackHeader: len " << len << "");

    if (len < 0) {
        debugs(90, 3, "WARNING: unpack error: " << xstrerr(xerrno));
        return false;
    }

    int swap_hdr_sz = 0;
    tlv *tlv_list = nullptr;
    try {
        StoreMetaUnpacker aBuilder(buf, len, &swap_hdr_sz);
        tlv_list = aBuilder.createStoreMeta();
    } catch (const std::exception &e) {
        debugs(90, DBG_IMPORTANT, "WARNING: failed to unpack metadata because " << e.what());
        return false;
    }
    assert(tlv_list);

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