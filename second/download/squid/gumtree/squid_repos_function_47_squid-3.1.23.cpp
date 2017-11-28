void
size2id(size_t sz, memitem * mi)
{
#ifdef WITH_LIB
    mi->pool = sizeToPool(sz);
    assert(mi->pool);
#endif
    return;
}