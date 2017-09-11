    if (!context) exit(1);
    while(1) {
        start = mstime();
        reply = redisCommand(context,"PING");
        if (reply == NULL) {
            fprintf(stderr,"\nI/O error\n");
            exit(1);
