    len->ptr = sdscatprintf(sdsempty(),"*%ld\r\n",length);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);

        /* Only glue when the next node is an sds */
        if (next->ptr != NULL) {
            len->ptr = sdscat(len->ptr,next->ptr);
            listDelNode(c->reply,ln->next);
        }
    }
