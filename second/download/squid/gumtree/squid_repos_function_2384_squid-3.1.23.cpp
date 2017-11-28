void
cacheDigestDel(CacheDigest * cd, const cache_key * key)
{
    assert(cd && key);
    cd->del_count++;
    /* we do not support deletions from the digest */
}