
    len = listNodeValue(ln);
    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
    len->encoding = REDIS_ENCODING_RAW; /* in case it was an EMBSTR. */
    c->reply_bytes += zmalloc_size_sds(len->ptr);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);
