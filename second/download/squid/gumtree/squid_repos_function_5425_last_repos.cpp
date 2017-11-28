static mem_type
memFindBufSizeType(size_t net_size, size_t * gross_size)
{
    mem_type type;
    size_t size;

    if (net_size <= 2 * 1024) {
        type = MEM_2K_BUF;
        size = 2 * 1024;
    } else if (net_size <= 4 * 1024) {
        type = MEM_4K_BUF;
        size = 4 * 1024;
    } else if (net_size <= 8 * 1024) {
        type = MEM_8K_BUF;
        size = 8 * 1024;
    } else if (net_size <= 16 * 1024) {
        type = MEM_16K_BUF;
        size = 16 * 1024;
    } else if (net_size <= 32 * 1024) {
        type = MEM_32K_BUF;
        size = 32 * 1024;
    } else if (net_size <= 64 * 1024) {
        type = MEM_64K_BUF;
        size = 64 * 1024;
    } else {
        type = MEM_NONE;
        size = net_size;
    }

    if (gross_size)
        *gross_size = size;

    return type;
}