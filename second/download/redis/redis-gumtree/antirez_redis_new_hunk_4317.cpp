    if (vmFindContiguousPages(&page,pages) == REDIS_ERR) return REDIS_ERR;
    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        redisLog(REDIS_WARNING,
            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
            strerror(errno));
        return REDIS_ERR;
    }
