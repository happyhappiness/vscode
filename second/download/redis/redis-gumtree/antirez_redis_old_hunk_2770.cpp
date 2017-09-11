    return out;
}

static int cliReadReply(int output_raw_strings) {
    void *_reply;
    redisReply *reply;
    sds out;
    int output = 1;

    if (redisGetReply(context,&_reply) != REDIS_OK) {
