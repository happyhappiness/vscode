static void vmInit(void) {
    off_t totsize;
    int pipefds[2];

    server.vm_fp = fopen("/tmp/redisvm","w+b");
    if (server.vm_fp == NULL) {
        redisLog(REDIS_WARNING,"Impossible to open the swap file. Exiting.");
        exit(1);
    }
    server.vm_fd = fileno(server.vm_fp);
    server.vm_next_page = 0;
    server.vm_near_pages = 0;
    server.vm_stats_used_pages = 0;
    server.vm_stats_swapped_objects = 0;
    server.vm_stats_swapouts = 0;
    server.vm_stats_swapins = 0;
    totsize = server.vm_pages*server.vm_page_size;
    redisLog(REDIS_NOTICE,"Allocating %lld bytes of swap file",totsize);
    if (ftruncate(server.vm_fd,totsize) == -1) {
        redisLog(REDIS_WARNING,"Can't ftruncate swap file: %s. Exiting.",
            strerror(errno));
        exit(1);
    } else {
        redisLog(REDIS_NOTICE,"Swap file allocated with success");
    }
    server.vm_bitmap = zmalloc((server.vm_pages+7)/8);
    redisLog(REDIS_VERBOSE,"Allocated %lld bytes page table for %lld pages",
        (long long) (server.vm_pages+7)/8, server.vm_pages);
    memset(server.vm_bitmap,0,(server.vm_pages+7)/8);
    /* Try to remove the swap file, so the OS will really delete it from the
     * file system when Redis exists. */
    unlink("/tmp/redisvm");

    /* Initialize threaded I/O (used by Virtual Memory) */
    server.io_newjobs = listCreate();
    server.io_processing = listCreate();
    server.io_processed = listCreate();
    server.io_clients = listCreate();
    pthread_mutex_init(&server.io_mutex,NULL);
    server.io_active_threads = 0;
    if (pipe(pipefds) == -1) {
        redisLog(REDIS_WARNING,"Unable to intialized VM: pipe(2): %s. Exiting."
            ,strerror(errno));
        exit(1);
    }
    server.io_ready_pipe_read = pipefds[0];
    server.io_ready_pipe_write = pipefds[1];
    redisAssert(anetNonBlock(NULL,server.io_ready_pipe_read) != ANET_ERR);
}