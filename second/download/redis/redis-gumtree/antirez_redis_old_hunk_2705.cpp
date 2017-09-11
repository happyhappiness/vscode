        reply3 = redisCommand(context,"%s %s", sizecmd, reply1->str);
        if (reply3 && reply3->type == REDIS_REPLY_INTEGER) {
            if (biggest[type] < reply3->integer) {
                printf("Biggest %s so far: %s, size: %llu\n",
                    typename[type], reply1->str,
                    (unsigned long long) reply3->integer);
                biggest[type] = reply3->integer;
