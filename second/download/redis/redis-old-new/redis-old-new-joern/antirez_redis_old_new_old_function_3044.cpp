static int cliSelect() {
    redisReply *reply;
    char dbnum[16];
    if (config.dbnum == 0) return REDIS_OK;

    snprintf(dbnum,sizeof(dbnum),"%d",config.dbnum);
    reply = redisCommand(context,"SELECT %s",dbnum);
    if (reply != NULL) {
        freeReplyObject(reply);
        return REDIS_OK;
    }
    return REDIS_ERR;
}