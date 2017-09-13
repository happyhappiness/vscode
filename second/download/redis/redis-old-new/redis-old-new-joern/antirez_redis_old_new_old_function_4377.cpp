static int compareStringObjects(robj *a, robj *b) {
    assert(a->type == REDIS_STRING && b->type == REDIS_STRING);

    if (a == b) return 0;
    if (a->encoding == REDIS_ENCODING_INT && b->encoding == REDIS_ENCODING_INT){
        return (long)a->ptr - (long)b->ptr;
    } else {
        int retval;

        incrRefCount(a);
        incrRefCount(b);
        if (a->encoding != REDIS_ENCODING_RAW) a = getDecodedObject(a);
        if (b->encoding != REDIS_ENCODING_RAW) b = getDecodedObject(a);
        retval = sdscmp(a->ptr,b->ptr);
        decrRefCount(a);
        decrRefCount(b);
        return retval;
    }
}