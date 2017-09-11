    redisContext *c;
    redisReply *reply;

    c = redisConnect((char*)"127.0.0.1", 6379);
    if (c->err) {
        printf("Connection error: %s\n", c->errstr);
        exit(1);
