        }

        /* Done: insert the job into the processed queue */
        redisLog(REDIS_DEBUG,"Thread %lld completed the job: %p\n",
            (long long) pthread_self(), (void*)j);
        lockThreadedIO();
        listDelNode(server.io_processing,ln);
