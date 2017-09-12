    return out;
}

static int cliReadReply() {
    redisReply *reply;
    sds out;

