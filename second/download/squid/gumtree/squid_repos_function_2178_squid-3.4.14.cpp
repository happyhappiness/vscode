static void
storeDigestCBlockSwapOut(StoreEntry * e)
{
    memset(&sd_state.cblock, 0, sizeof(sd_state.cblock));
    sd_state.cblock.ver.current = htons(CacheDigestVer.current);
    sd_state.cblock.ver.required = htons(CacheDigestVer.required);
    sd_state.cblock.capacity = htonl(store_digest->capacity);
    sd_state.cblock.count = htonl(store_digest->count);
    sd_state.cblock.del_count = htonl(store_digest->del_count);
    sd_state.cblock.mask_size = htonl(store_digest->mask_size);
    sd_state.cblock.bits_per_entry = (unsigned char)
                                     Config.digest.bits_per_entry;
    sd_state.cblock.hash_func_count = (unsigned char) CacheDigestHashFuncCount;
    e->append((char *) &sd_state.cblock, sizeof(sd_state.cblock));
}