int
MemBuf::isNull()
{
    if (!buf && !max_capacity && !capacity && !size)
        return 1;       /* is null (not initialized) */

    assert(buf && max_capacity && capacity);    /* paranoid */

    return 0;
}