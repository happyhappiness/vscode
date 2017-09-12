void addReplyDouble(redisClient *c, double d) {
    char buf[128];

    snprintf(buf,sizeof(buf),"%.17g",d);
    addReplySds(c,sdscatprintf(sdsempty(),"$%lu\r\n%s\r\n",
        (unsigned long) strlen(buf),buf));
}