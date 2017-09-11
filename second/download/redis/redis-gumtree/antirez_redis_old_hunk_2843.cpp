
sds sdscatrepr(sds s, char *p, size_t len) {
    s = sdscatlen(s,"\"",1);
    while(len--) {
        switch(*p) {
        case '\\':
        case '"':
            s = sdscatprintf(s,"\\%c",*p);
            break;
        case '\n': s = sdscatlen(s,"\\n",1); break;
        case '\r': s = sdscatlen(s,"\\r",1); break;
        case '\t': s = sdscatlen(s,"\\t",1); break;
        case '\a': s = sdscatlen(s,"\\a",1); break;
        case '\b': s = sdscatlen(s,"\\b",1); break;
        default:
            if (isprint(*p))
                s = sdscatprintf(s,"%c",*p);
