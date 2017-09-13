static robj *getDecodedObject(const robj *o) {
    robj *dec;
    
    assert(o->encoding != REDIS_ENCODING_RAW);
    if (o->type == REDIS_STRING && o->encoding == REDIS_ENCODING_INT) {
        char buf[32];

        snprintf(buf,32,"%ld",(long)o->ptr);
        dec = createStringObject(buf,strlen(buf));
        return dec;
    } else {
        assert(1 != 1);
    }
}