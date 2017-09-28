sds reply = sdscatprintf(sdsempty(),"+%s %llu\r\n",
                (retval == REDIS_OK) ? "BUMPED" : "STILL",
                (unsigned long long) myself->configEpoch);