cache_key *
storeKeyDup(const cache_key * key)
{
    cache_key *dup = (cache_key *)memAllocate(MEM_MD5_DIGEST);
    memcpy(dup, key, SQUID_MD5_DIGEST_LENGTH);
    return dup;
}