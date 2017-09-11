
static void setProtocolError(redisClient *c, int pos);


/* Return the amount of memory used by the sds string at object->ptr
 * for a string object. */
size_t getStringObjectSdsUsedMemory(robj *o) {
    redisAssertWithInfo(NULL,o,o->type == REDIS_STRING);
    switch(o->encoding) {
    case REDIS_ENCODING_RAW: return sdsZmallocSize(o->ptr);
    case REDIS_ENCODING_EMBSTR: return zmalloc_size(o)-sizeof(robj);
    default: return 0; /* Just integer encoding for now. */
    }
}
