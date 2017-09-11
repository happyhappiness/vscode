        /* Set the max number of files if the current limit is not enough
         * for our needs. */
        if (oldlimit < maxfiles) {
            rlim_t f;
            
            f = maxfiles;
            while(f > oldlimit) {
                limit.rlim_cur = f;
                limit.rlim_max = f;
                if (setrlimit(RLIMIT_NOFILE,&limit) != -1) break;
                f -= 128;
            }
            if (f < oldlimit) f = oldlimit;
            if (f != maxfiles) {
                server.maxclients = f-32;
                redisLog(REDIS_WARNING,"Unable to set the max number of files limit to %d (%s), setting the max clients configuration to %d.",
                    (int) maxfiles, strerror(errno), (int) server.maxclients);
            } else {
