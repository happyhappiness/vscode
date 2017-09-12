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
