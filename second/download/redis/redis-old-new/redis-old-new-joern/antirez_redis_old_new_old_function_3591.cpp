sds sdstrim(sds s, const char *cset) {
    struct sdshdr *sh = (void*) (s-(sizeof(struct sdshdr)));
    char *start, *end, *sp, *ep;
    size_t len;

    sp = start = s;
    ep = end = s+sdslen(s)-1;
    while(sp <= end && strchr(cset, *sp)) sp++;
    while(ep > start && strchr(cset, *ep)) ep--;
    len = (sp > ep) ? 0 : ((ep-sp)+1);
    if (sh->buf != sp) memmove(sh->buf, sp, len);
    sh->buf[len] = '\0';
    sh->free = sh->free+(sh->len-len);
    sh->len = len;
    return s;
}