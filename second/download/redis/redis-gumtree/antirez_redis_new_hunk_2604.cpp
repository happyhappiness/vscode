        reply3 = redisCommand(context,"%s %s", sizecmd, reply1->str);
        if (reply3 && reply3->type == REDIS_REPLY_INTEGER) {
            if (biggest[type] < reply3->integer) {
                printf("Biggest %-6s found so far '%s' with %llu %s.\n",
                    typename[type], reply1->str,
                    (unsigned long long) reply3->integer,
                    typeunit[type]);
                biggest[type] = reply3->integer;
            }
        }
