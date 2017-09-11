
    len = listNodeValue(ln);
    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);

