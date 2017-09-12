    off_t totsize;
    int pipefds[2];
    size_t stacksize;

    if (server.vm_max_threads != 0)
        zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */

    expandVmSwapFilename();
    redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
    if ((server.vm_fp = fopen(server.vm_swap_file,"r+b")) == NULL) {
        server.vm_fp = fopen(server.vm_swap_file,"w+b");
    }
    if (server.vm_fp == NULL) {
        redisLog(REDIS_WARNING,
            "Impossible to open the swap file: %s. Exiting.",
            strerror(errno));
        exit(1);
    }
    server.vm_fd = fileno(server.vm_fp);
    server.vm_next_page = 0;
    server.vm_near_pages = 0;
    server.vm_stats_used_pages = 0;
