void
CacheDigest::clear()
{
    count = del_count = 0;
    memset(mask, 0, mask_size);
}