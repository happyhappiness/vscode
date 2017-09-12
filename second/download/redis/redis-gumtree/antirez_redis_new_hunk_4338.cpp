    unlink(tmpfile);
}

/* =============================== Virtual Memory =========================== */
static void vmInit(void) {
    off_t totsize;

    server.vm_fp = fopen("/tmp/redisvm","w+b");
    if (server.vm_fp == NULL) {
        redisLog(REDIS_WARNING,"Impossible to open the swap file. Exiting.");
        exit(1);
    }
    server.vm_fd = fileno(server.vm_fp);
    server.vm_next_page = 0;
    server.vm_near_pages = 0;
    totsize = server.vm_pages*server.vm_page_size;
    redisLog(REDIS_NOTICE,"Allocating %lld bytes of swap file",totsize);
    if (ftruncate(server.vm_fd,totsize) == -1) {
        redisLog(REDIS_WARNING,"Can't ftruncate swap file: %s. Exiting.",
            strerror(errno));
        exit(1);
    } else {
        redisLog(REDIS_NOTICE,"Swap file allocated with success");
    }
    /* Try to remove the swap file, so the OS will really delete it from the
     * file system when Redis exists. */
    unlink("/tmp/redisvm");
}

/* ================================= Debugging ============================== */

static void debugCommand(redisClient *c) {
