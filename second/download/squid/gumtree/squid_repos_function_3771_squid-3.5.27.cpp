void MemBuf::consume(mb_size_t shiftSize)
{
    const mb_size_t cSize = contentSize();
    assert(0 <= shiftSize && shiftSize <= cSize);
    assert(!stolen); /* not frozen */

    PROF_start(MemBuf_consume);
    if (shiftSize > 0) {
        if (shiftSize < cSize)
            memmove(buf, buf + shiftSize, cSize - shiftSize);

        size -= shiftSize;

        terminate();
    }
    PROF_stop(MemBuf_consume);
}