    dictEntry *de;
    sds line;

    /* For every master emit a "sentinel monitor" config entry. */
    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
