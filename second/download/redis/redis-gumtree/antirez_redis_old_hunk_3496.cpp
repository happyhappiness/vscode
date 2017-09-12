    exit(1);
}

static sds cliFormatReply(redisReply *r, char *prefix) {
    sds out = sdsempty();
    switch (r->type) {
    case REDIS_REPLY_ERROR:
        if (config.tty) out = sdscat(out,"(error) ");
        out = sdscatprintf(out,"%s\n", r->str);
    break;
    case REDIS_REPLY_STATUS:
        out = sdscat(out,r->str);
        out = sdscat(out,"\n");
    break;
    case REDIS_REPLY_INTEGER:
        if (config.tty) out = sdscat(out,"(integer) ");
        out = sdscatprintf(out,"%lld\n",r->integer);
    break;
    case REDIS_REPLY_STRING:
        if (config.raw_output || !config.tty) {
            out = sdscatlen(out,r->str,r->len);
        } else {
            /* If you are producing output for the standard output we want
             * a more interesting output with quoted characters and so forth */
            out = sdscatrepr(out,r->str,r->len);
            out = sdscat(out,"\n");
        }
    break;
    case REDIS_REPLY_NIL:
        out = sdscat(out,"(nil)\n");
