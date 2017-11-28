bool
storeRebuildParseEntry(MemBuf &buf, StoreEntry &tmpe, cache_key *key,
                       StoreRebuildData &counts,
                       uint64_t expectedSize)
{
    int swap_hdr_len = 0;
    StoreMetaUnpacker aBuilder(buf.content(), buf.contentSize(), &swap_hdr_len);
    if (aBuilder.isBufferZero()) {
        debugs(47,5, HERE << "skipping empty record.");
        return false;
    }

    if (!aBuilder.isBufferSane()) {
        debugs(47, DBG_IMPORTANT, "WARNING: Ignoring malformed cache entry.");
        return false;
    }

    StoreMeta *tlv_list = aBuilder.createStoreMeta();
    if (!tlv_list) {
        debugs(47, DBG_IMPORTANT, "WARNING: Ignoring cache entry with invalid " <<
               "meta data");
        return false;
    }

    // TODO: consume parsed metadata?

    debugs(47,7, HERE << "successful swap meta unpacking");
    memset(key, '\0', SQUID_MD5_DIGEST_LENGTH);

    InitStoreEntry visitor(&tmpe, key);
    for_each(*tlv_list, visitor);
    storeSwapTLVFree(tlv_list);
    tlv_list = NULL;

    if (storeKeyNull(key)) {
        debugs(47, DBG_IMPORTANT, "WARNING: Ignoring keyless cache entry");
        return false;
    }

    tmpe.key = key;
    /* check sizes */

    if (expectedSize > 0) {
        if (tmpe.swap_file_sz == 0) {
            tmpe.swap_file_sz = expectedSize;
        } else if (tmpe.swap_file_sz == (uint64_t)(expectedSize - swap_hdr_len)) {
            tmpe.swap_file_sz = expectedSize;
        } else if (tmpe.swap_file_sz != expectedSize) {
            debugs(47, DBG_IMPORTANT, "WARNING: Ignoring cache entry due to a " <<
                   "SIZE MISMATCH " << tmpe.swap_file_sz << "!=" << expectedSize);
            return false;
        }
    } else if (tmpe.swap_file_sz <= 0) {
        debugs(47, DBG_IMPORTANT, "WARNING: Ignoring cache entry with " <<
               "unknown size: " << tmpe);
        return false;
    }

    if (EBIT_TEST(tmpe.flags, KEY_PRIVATE)) {
        ++ counts.badflags;
        return false;
    }

    return true;
}