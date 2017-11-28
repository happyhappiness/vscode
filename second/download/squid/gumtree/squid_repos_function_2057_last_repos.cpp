void
CacheDigest::remove(const cache_key * key)
{
    assert(key);
    ++del_count;
    /* we do not support deletions from the digest */
}