void
MemBuf::grow(mb_size_t min_cap)
{
    size_t new_cap;
    size_t buf_cap;

    assert(!stolen);
    assert(capacity < min_cap);

    PROF_start(MemBuf_grow);

    /* determine next capacity */

    if (min_cap > 64 * 1024) {
        new_cap = 64 * 1024;

        while (new_cap < (size_t) min_cap)
            new_cap += 64 * 1024;   /* increase in reasonable steps */
    } else {
        new_cap = (size_t) min_cap;
    }

    /* last chance to fit before we assert(!overflow) */
    if (new_cap > (size_t) max_capacity)
        new_cap = (size_t) max_capacity;

    assert(new_cap <= (size_t) max_capacity);   /* no overflow */

    assert(new_cap > (size_t) capacity);    /* progress */

    buf_cap = (size_t) capacity;

    buf = (char *)memReallocBuf(buf, new_cap, &buf_cap);

    /* done */
    capacity = (mb_size_t) buf_cap;
    PROF_stop(MemBuf_grow);
}