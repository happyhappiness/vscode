static sds cliFormatReply(redisReply *r, char *prefix) {
    sds out = sdsempty();
    switch (r->type) {
    case REDIS_REPLY_ERROR:
        out = sdscat(out,prefix);
        if (config.tty) out = sdscat(out,"(error) ");
        out = sdscatprintf(out,"%s\n", r->str);
    break;
    case REDIS_REPLY_STATUS:
        out = sdscat(out,prefix);
        out = sdscat(out,r->str);
        out = sdscat(out,"\n");
    break;
    case REDIS_REPLY_INTEGER:
        out = sdscat(out,prefix);
        if (config.tty) out = sdscat(out,"(integer) ");
        out = sdscatprintf(out,"%lld\n",r->integer);
    break;
    case REDIS_REPLY_STRING:
        out = sdscat(out,prefix);
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
        out = sdscat(out,prefix);
        out = sdscat(out,"(nil)\n");
    break;
    case REDIS_REPLY_ARRAY:
        if (r->elements == 0) {
            out = sdscat(out,prefix);
            out = sdscat(out,"(empty list or set)\n");
        } else {
            unsigned int i;
            sds tmp;

            for (i = 0; i < r->elements; i++) {
                tmp = cliFormatReply(r->element[i],prefix);
                out = sdscat(out,prefix);
                out = sdscatlen(out,tmp,sdslen(tmp));
                sdsfree(tmp);
            }
        }
    break;
    default:
        fprintf(stderr,"Unknown reply type: %d\n", r->type);
        exit(1);
    }
    return out;
}