    off_t byte = page/8;
    int bit = page&7;
    server.vm_bitmap[byte] |= 1<<bit;
    redisLog(REDIS_DEBUG,"Mark used: %lld (byte:%lld bit:%d)\n",
        (long long)page, (long long)byte, bit);
}

/* Mark N contiguous pages as used, with 'page' being the first. */
