void _addReplyStringToList(redisClient *c, char *s, size_t len) {
    robj *tail;
    if (listLength(c->reply) == 0) {
        listAddNodeTail(c->reply,createStringObject(s,len));
    } else {
        tail = listNodeValue(listLast(c->reply));

        /* Append to this object when possible. */
        if (tail->ptr != NULL &&
            sdslen(tail->ptr)+len <= REDIS_REPLY_CHUNK_BYTES)
        {
            tail = dupLastObjectIfNeeded(c->reply);
            tail->ptr = sdscatlen(tail->ptr,s,len);
        } else {
            listAddNodeTail(c->reply,createStringObject(s,len));
        }
    }
}