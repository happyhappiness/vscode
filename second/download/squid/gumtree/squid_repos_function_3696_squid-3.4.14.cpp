void
MemBuf::clean()
{
    if (isNull()) {
        // nothing to do
    } else {
        assert(buf);
        assert(!stolen);	/* not frozen */

        memFreeBuf(capacity, buf);
        buf = NULL;
        size = capacity = max_capacity = 0;
    }
}