    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    }
    zfree(dv);
}

static void sinterCommand(redisClient *c) {
