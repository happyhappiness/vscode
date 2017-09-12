        }
    }
    hashTypeReleaseIterator(hi);

    lenobj->ptr = sdscatprintf(sdsempty(),"*%lu\r\n",count);
}

void hkeysCommand(redisClient *c) {
