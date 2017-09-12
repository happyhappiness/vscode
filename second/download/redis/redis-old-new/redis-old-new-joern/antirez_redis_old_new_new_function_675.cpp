void setDeferredMultiBulkLength(client *c, void *node, long length) {
    listNode *ln = (listNode*)node;
    sds len, next;

    /* Abort when *node is NULL: when the client should not accept writes
     * we return NULL in addDeferredMultiBulkLength() */
    if (node == NULL) return;

    len = sdscatprintf(sdsnewlen("*",1),"%ld\r\n",length);
    listNodeValue(ln) = len;
    c->reply_bytes += sdslen(len);
    if (ln->next != NULL) {
        next = listNodeValue(ln->next);

        /* Only glue when the next node is non-NULL (an sds in this case) */
        if (next != NULL) {
            len = sdscatsds(len,next);
            listDelNode(c->reply,ln->next);
            listNodeValue(ln) = len;
            /* No need to update c->reply_bytes: we are just moving the same
             * amount of bytes from one node to another. */
        }
    }
    asyncCloseClientOnOutputBufferLimitReached(c);
}