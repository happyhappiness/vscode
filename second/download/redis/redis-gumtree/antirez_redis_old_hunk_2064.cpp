        shared.bulkhdr[j] = createObject(REDIS_STRING,
            sdscatprintf(sdsempty(),"$%d\r\n",j));
    }
}

void initServerConfig() {
