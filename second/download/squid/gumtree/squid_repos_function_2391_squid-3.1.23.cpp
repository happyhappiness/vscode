static void
cacheDigestHashKey(const CacheDigest * cd, const cache_key * key)
{
    const unsigned int bit_count = cd->mask_size * 8;
    unsigned int tmp_keys[4];
    /* we must memcpy to ensure alignment */
    xmemcpy(tmp_keys, key, sizeof(tmp_keys));
    hashed_keys[0] = htonl(tmp_keys[0]) % bit_count;
    hashed_keys[1] = htonl(tmp_keys[1]) % bit_count;
    hashed_keys[2] = htonl(tmp_keys[2]) % bit_count;
    hashed_keys[3] = htonl(tmp_keys[3]) % bit_count;
    debugs(70, 9, "cacheDigestHashKey: " << storeKeyText(key) << " -(" <<
           bit_count << ")-> " << hashed_keys[0] << " " << hashed_keys[1] <<
           " " << hashed_keys[2] << " " << hashed_keys[3]);
}