static void
cacheDigestClean(CacheDigest * cd)
{
    assert(cd);
    xfree(cd->mask);
    cd->mask = NULL;
}