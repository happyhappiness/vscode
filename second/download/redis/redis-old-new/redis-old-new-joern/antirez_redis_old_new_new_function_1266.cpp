static void LRUTestMode(void) {
    redisReply *reply;
    char key[128];
    long long start_cycle;
    int j;

    srand(time(NULL)^getpid());
    while(1) {
        /* Perform cycles of 1 second with 50% writes and 50% reads.
         * We use pipelining batching writes / reads N times per cycle in order
         * to fill the target instance easily. */
        start_cycle = mstime();
        long long hits = 0, misses = 0;
        while(mstime() - start_cycle < 1000) {
            /* Write cycle. */
            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++) {
                LRUTestGenKey(key,sizeof(key));
                redisAppendCommand(context, "SET %s val",key);
            }
            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++)
                redisGetReply(context, (void**)&reply);

            /* Read cycle. */
            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++) {
                LRUTestGenKey(key,sizeof(key));
                redisAppendCommand(context, "GET %s",key);
            }
            for (j = 0; j < LRU_CYCLE_PIPELINE_SIZE; j++) {
                if (redisGetReply(context, (void**)&reply) == REDIS_OK) {
                    switch(reply->type) {
                        case REDIS_REPLY_ERROR:
                            printf("%s\n", reply->str);
                            break;
                        case REDIS_REPLY_NIL:
                            misses++;
                            break;
                        default:
                            hits++;
                            break;
                    }
                }
            }

            if (context->err) {
                fprintf(stderr,"I/O error during LRU test\n");
                exit(1);
            }
        }
        /* Print stats. */
        printf(
            "%lld Gets/sec | Hits: %lld (%.2f%%) | Misses: %lld (%.2f%%)\n",
            hits+misses,
            hits, (double)hits/(hits+misses)*100,
            misses, (double)misses/(hits+misses)*100);
    }
    exit(0);
}