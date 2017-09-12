    off_t byte = page/8;
    int bit = page&7;
    server.vm_bitmap[byte] |= 1<<bit;
    printf("Mark used: %lld (byte:%d bit:%d)\n", (long long)page, byte, bit);
}

/* Mark N contiguous pages as used, with 'page' being the first. */
static void vmMarkPagesUsed(off_t page, off_t count) {
    off_t j;

    for (j = 0; j < count; j++)
        vmMarkPageUsed(page+j);
}

/* Mark the page as free */
