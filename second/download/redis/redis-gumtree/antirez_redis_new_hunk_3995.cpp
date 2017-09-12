    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    }
    zfree(sets);
}

static void sinterCommand(redisClient *c) {
