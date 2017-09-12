
/* =================== Virtual Memory - Blocking Side  ====================== */

void vmInit(void) {
    off_t totsize;
    int pipefds[2];
    size_t stacksize;
    struct flock fl;

    if (server.vm_max_threads != 0)
        zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */

    redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
    /* Try to open the old swap file, otherwise create it */
    if ((server.vm_fp = fopen(server.vm_swap_file,"r+b")) == NULL) {
        server.vm_fp = fopen(server.vm_swap_file,"w+b");
    }
    if (server.vm_fp == NULL) {
        redisLog(REDIS_WARNING,
            "Can't open the swap file: %s. Exiting.",
            strerror(errno));
        exit(1);
    }
    server.vm_fd = fileno(server.vm_fp);
    /* Lock the swap file for writing, this is useful in order to avoid
     * another instance to use the same swap file for a config error. */
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = fl.l_len = 0;
    if (fcntl(server.vm_fd,F_SETLK,&fl) == -1) {
        redisLog(REDIS_WARNING,
            "Can't lock the swap file at '%s': %s. Make sure it is not used by another Redis instance.", server.vm_swap_file, strerror(errno));
        exit(1);
    }
    /* Initialize */
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
    server.vm_bitmap = zcalloc((server.vm_pages+7)/8);
    redisLog(REDIS_VERBOSE,"Allocated %lld bytes page table for %lld pages",
        (long long) (server.vm_pages+7)/8, server.vm_pages);

    /* Initialize threaded I/O (used by Virtual Memory) */
    server.io_newjobs = listCreate();
    server.io_processing = listCreate();
    server.io_processed = listCreate();
    server.io_ready_clients = listCreate();
    pthread_mutex_init(&server.io_mutex,NULL);
    pthread_mutex_init(&server.io_swapfile_mutex,NULL);
    server.io_active_threads = 0;
    if (pipe(pipefds) == -1) {
        redisLog(REDIS_WARNING,"Unable to intialized VM: pipe(2): %s. Exiting."
            ,strerror(errno));
        exit(1);
    }
