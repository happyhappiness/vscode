        lockThreadedIO();
        if (listLength(server.io_newjobs) == 0) {
            /* No new jobs in queue, exit. */
            redisLog(REDIS_DEBUG,"Thread %lld exiting, nothing to do\n",
                (long long) pthread_self());
            server.io_active_threads--;
            unlockThreadedIO();
