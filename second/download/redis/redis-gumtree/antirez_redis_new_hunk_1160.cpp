
    len = listNodeValue(ln);
    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
    len->encoding = OBJ_ENCODING_RAW; /* in case it was an EMBSTR. */
    c->reply_bytes += sdsZmallocSize(len->ptr);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);
