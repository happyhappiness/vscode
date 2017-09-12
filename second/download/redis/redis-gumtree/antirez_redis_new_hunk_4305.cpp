    return REDIS_ERR;
}

/* Write the specified object at the specified page of the swap file */
static int vmWriteObjectOnSwap(robj *o, off_t page) {
    if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
    if (fseeko(server.vm_fp,page*server.vm_page_size,SEEK_SET) == -1) {
        if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
        redisLog(REDIS_WARNING,
            "Critical VM problem in vmSwapObjectBlocking(): can't seek: %s",
            strerror(errno));
        return REDIS_ERR;
    }
    rdbSaveObject(server.vm_fp,o);
    if (server.vm_enabled) pthread_mutex_unlock(&server.io_swapfile_mutex);
    return REDIS_OK;
}

/* Swap the 'val' object relative to 'key' into disk. Store all the information
 * needed to later retrieve the object into the key object.
 * If we can't find enough contiguous empty pages to swap the object on disk
