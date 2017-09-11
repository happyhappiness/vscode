    return out;
}

static int cliReadReply(int output_raw_strings) {
    void *_reply;
    redisReply *reply;
