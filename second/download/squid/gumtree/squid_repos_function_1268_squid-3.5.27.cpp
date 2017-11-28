void
memFreeBuf(size_t size, void *buf)
{
    mem_type type = memFindBufSizeType(size, NULL);

    if (type != MEM_NONE)
        memFree(buf, type);
    else {
        xfree(buf);
        memMeterDec(HugeBufCountMeter);
        memMeterDel(HugeBufVolumeMeter, size);
    }
}