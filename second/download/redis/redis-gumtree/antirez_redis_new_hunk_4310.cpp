        listAddNodeTail(server.io_processing,j);
        ln = listLast(server.io_processing); /* We use ln later to remove it */
        unlockThreadedIO();
        redisLog(REDIS_DEBUG,"Thread %lld got a new job: %p about key '%s'\n",
            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);

        /* Process the Job */
