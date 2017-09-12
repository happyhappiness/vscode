
    expandVmSwapFilename();
    redisLog(REDIS_NOTICE,"Using '%s' as swap file",server.vm_swap_file);
    server.vm_fp = fopen(server.vm_swap_file,"r+b");
    if (server.vm_fp == NULL) {
        redisLog(REDIS_WARNING,"Impossible to open the swap file. Exiting.");
        exit(1);
    }
    server.vm_fd = fileno(server.vm_fp);
