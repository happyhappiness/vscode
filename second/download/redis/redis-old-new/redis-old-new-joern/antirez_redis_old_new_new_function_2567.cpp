void addReplyError(redisClient *c, char *err) {
    addReplyErrorLength(c,err,strlen(err));
}