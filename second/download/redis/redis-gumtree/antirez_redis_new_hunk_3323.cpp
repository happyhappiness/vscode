/* Send SELECT dbnum to the server */
static int cliSelect() {
    redisReply *reply;
    if (config.dbnum == 0) return REDIS_OK;

    reply = redisCommand(context,"SELECT %d",config.dbnum);
    if (reply != NULL) {
        freeReplyObject(reply);
        return REDIS_OK;
