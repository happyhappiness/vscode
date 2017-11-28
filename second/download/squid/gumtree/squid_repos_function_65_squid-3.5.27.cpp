FREE *
MemBuf::freeFunc()
{
    FREE *ff;
    assert(buf);
    assert(!stolen);    /* not frozen */

    ff = memFreeBufFunc((size_t) capacity);
    stolen = 1;     /* freeze */
    return ff;
}