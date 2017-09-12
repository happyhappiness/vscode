    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);
        /* Only glue when the next node is a reply chunk. */
        if (next->type == REDIS_REPLY_NODE) {
            len->ptr = sdscatlen(len->ptr,next->ptr,sdslen(next->ptr));
            listDelNode(c->reply,ln->next);
        }
    }
