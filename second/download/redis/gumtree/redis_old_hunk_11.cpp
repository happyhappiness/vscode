    } while(v);
    if (value < 0) *p-- = '-';
    p++;
    return sdsnewlen(p,32-(p-buf));
}

sds sdscatrepr(sds s, char *p, size_t len) {
    s = sdscatlen(s,"\"",1);
    if (s == NULL) return NULL;

    while(len--) {
        switch(*p) {
        case '\\':
        case '"':
            s = sdscatprintf(s,"\\%c",*p);
            break;
