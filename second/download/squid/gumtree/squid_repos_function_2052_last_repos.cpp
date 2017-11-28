CacheDigest *
CacheDigest::clone() const
{
    CacheDigest *cl = new CacheDigest(capacity, bits_per_entry);
    cl->count = count;
    cl->del_count = del_count;
    assert(mask_size == cl->mask_size);
    memcpy(cl->mask, mask, mask_size);
    return cl;
}