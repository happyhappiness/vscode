void
cacheDigestDestroy(CacheDigest * cd)
{
    assert(cd);
    cacheDigestClean(cd);
    memFree(cd, MEM_CACHE_DIGEST);
}