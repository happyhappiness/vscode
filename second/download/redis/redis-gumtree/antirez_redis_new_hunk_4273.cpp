    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
        redisLog(REDIS_WARNING,
            "Critical VM problem in vmWriteObjectOnSwap(): can't seek: %s",
            strerror(errno));
        return REDIS_ERR;
    }
