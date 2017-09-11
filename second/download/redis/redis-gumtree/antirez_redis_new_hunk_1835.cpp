uxeof: /* Unexpected AOF end of file. */
    if (server.aof_load_truncated) {
        redisLog(REDIS_WARNING,"!!! Warning: short read while loading the AOF file !!!");
        redisLog(REDIS_WARNING,"!!! Truncating the AOF at offset %llu !!!",
            (unsigned long long) valid_up_to);
        if (valid_up_to == -1 || truncate(filename,valid_up_to) == -1) {
            if (valid_up_to == -1) {
                redisLog(REDIS_WARNING,"Last valid command offset is invalid");
            } else {
                redisLog(REDIS_WARNING,"Error truncating the AOF file: %s",
                    strerror(errno));
            }
        } else {
            redisLog(REDIS_WARNING,
                "AOF loaded anyway because aof-load-truncated is enabled");
            goto loaded_ok;
        }
    }
    redisLog(REDIS_WARNING,"Unexpected end of file reading the append only file. You can: 1) Make a backup of your AOF file, then use ./redis-check-aof --fix <filename>. 2) Alternatively you can set the 'aof-load-truncated' configuration option to yes and restart the server.");
    exit(1);
