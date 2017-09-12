static void latencyMode(void) {
    redisReply *reply;
    long long start, latency, min = 0, max = 0, tot = 0, count = 0;
    long long history_interval =
        config.interval ? config.interval/1000 :
                          LATENCY_HISTORY_DEFAULT_INTERVAL;
    double avg;
    long long history_start = mstime();

    if (!context) exit(1);
    while(1) {
        start = mstime();
        reply = redisCommand(context,"PING");
        if (reply == NULL) {
            fprintf(stderr,"\nI/O error\n");
            exit(1);
        }
        latency = mstime()-start;
        freeReplyObject(reply);
        count++;
        if (count == 1) {
            min = max = tot = latency;
            avg = (double) latency;
        } else {
            if (latency < min) min = latency;
            if (latency > max) max = latency;
            tot += latency;
            avg = (double) tot/count;
        }
        printf("\x1b[0G\x1b[2Kmin: %lld, max: %lld, avg: %.2f (%lld samples)",
            min, max, avg, count);
        fflush(stdout);
        if (config.latency_history && mstime()-history_start > history_interval)
        {
            printf(" -- %.2f seconds range\n", (float)(mstime()-history_start)/1000);
            history_start = mstime();
            min = max = tot = count = 0;
        }
        usleep(LATENCY_SAMPLE_RATE * 1000);
    }
}