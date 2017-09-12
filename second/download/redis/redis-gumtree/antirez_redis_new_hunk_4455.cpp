    }
}

static size_t stringObjectLen(robj *o) {
    assert(o->type == REDIS_STRING);
    if (o->encoding == REDIS_ENCODING_RAW) {
        return sdslen(o->ptr);
    } else {
        char buf[32];

        return snprintf(buf,32,"%ld",(long)o->ptr);
    }
}

/*============================ DB saving/loading ============================ */

static int rdbSaveType(FILE *fp, unsigned char type) {
