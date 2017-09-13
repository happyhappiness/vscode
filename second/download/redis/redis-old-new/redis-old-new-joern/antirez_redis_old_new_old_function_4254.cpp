static void vmMarkPageUsed(off_t page) {
    off_t byte = page/8;
    int bit = page&7;
    server.vm_bitmap[byte] |= 1<<bit;
    printf("Mark used: %lld (byte:%lld bit:%d)\n", (long long)page,
        (long long)byte, bit);
}