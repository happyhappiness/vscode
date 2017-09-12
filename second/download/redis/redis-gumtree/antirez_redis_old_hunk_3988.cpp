    } else {
        lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",cardinality);
    }
    zfree(dv);
}

void sinterCommand(redisClient *c) {
