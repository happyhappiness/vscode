    double avg;
    long long history_start = mstime();

    if (!context) exit(1);
    while(1) {
        start = mstime();
        reply = reconnectingRedisCommand(context,"PING");
        if (reply == NULL) {
            fprintf(stderr,"\nI/O error\n");
            exit(1);
        }
        latency = mstime()-start;
        freeReplyObject(reply);
