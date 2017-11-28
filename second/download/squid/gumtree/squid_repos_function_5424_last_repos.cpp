void
memFreeString(size_t size, void *buf)
{
    assert(buf);

    auto type = memFindStringSizeType(size, false);
    if (type != MEM_NONE)
        GetStrPool(type).freeOne(buf);
    else
        xfree(buf);

    --StrCountMeter;
    StrVolumeMeter -= size;
}