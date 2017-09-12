        (float)self_ru.ru_stime.tv_sec+(float)self_ru.ru_stime.tv_usec/1000000,
        (float)c_ru.ru_utime.tv_sec+(float)c_ru.ru_utime.tv_usec/1000000,
        (float)c_ru.ru_stime.tv_sec+(float)c_ru.ru_stime.tv_usec/1000000);

        numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
        for (j = 0; j < numcommands; j++) {
            struct redisCommand *c = readonlyCommandTable+j;
            info = sdscatprintf(info,"used_time_cmd_%s:%lld\r\n",
                c->name, c->microseconds);
        }
    }

