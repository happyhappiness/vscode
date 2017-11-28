CacheDigest *
cacheDigestCreate(uint64_t capacity, uint8_t bpe)
{
    CacheDigest *cd = (CacheDigest *)memAllocate(MEM_CACHE_DIGEST);
    assert(SQUID_MD5_DIGEST_LENGTH == 16);  /* our hash functions rely on 16 byte keys */
    cacheDigestInit(cd, capacity, bpe);
    return cd;
}