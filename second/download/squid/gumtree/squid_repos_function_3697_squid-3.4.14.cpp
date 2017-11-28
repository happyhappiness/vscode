void
MemBuf::reset()
{
    if (isNull()) {
        init();
    } else {
        assert(!stolen);	/* not frozen */
        /* reset */
        memset(buf, 0, capacity);
        size = 0;
    }
}