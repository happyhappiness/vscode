void addReplyError(redisClient *c, char *err) {
    _addReplyError(c,err,strlen(err));
}