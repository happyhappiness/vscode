        }
    }
    dictReleaseIterator(di);
    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",numkeys);
}

void dbsizeCommand(redisClient *c) {
