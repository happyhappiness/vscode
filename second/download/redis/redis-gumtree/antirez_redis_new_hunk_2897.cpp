
    len = listNodeValue(ln);
    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
    c->reply_bytes += sdslen(len->ptr);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);

