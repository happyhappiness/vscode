void *
memAllocBuf(size_t net_size, size_t * gross_size)
{
    mem_type type = memFindBufSizeType(net_size, gross_size);

    if (type != MEM_NONE)
        return memAllocate(type);
    else {
        ++HugeBufCountMeter;
        HugeBufVolumeMeter += *gross_size;
        return xcalloc(1, net_size);
    }
}