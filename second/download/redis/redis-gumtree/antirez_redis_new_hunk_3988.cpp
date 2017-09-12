    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    }
    zfree(sets);
}

void sinterCommand(redisClient *c) {
