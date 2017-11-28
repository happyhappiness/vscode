FREE *
memFreeBufFunc(size_t size)
{
    switch (size) {

    case 2 * 1024:
        return memFree2K;

    case 4 * 1024:
        return memFree4K;

    case 8 * 1024:
        return memFree8K;

    case 16 * 1024:
        return memFree16K;

    case 32 * 1024:
        return memFree32K;

    case 64 * 1024:
        return memFree64K;

    default:
        memMeterDec(HugeBufCountMeter);
        memMeterDel(HugeBufVolumeMeter, size);
        return xfree;
    }
}