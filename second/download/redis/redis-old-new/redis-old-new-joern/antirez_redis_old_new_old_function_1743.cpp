static void findBigKeys(void) {
    unsigned long long biggest[5] = {0,0,0,0,0};
    unsigned long long samples = 0;
    redisReply *reply1, *reply2, *reply3 = NULL, *keys;
    char *key, *sizecmd, *typename[] = {"string","list","set","hash","zset"};
    char *typeunit[] = {"bytes","items","members","fields","members"};
    int type, it=0, i;

    printf("\n# Press ctrl+c when you have had enough of it... :)\n");
    printf("# You can use -i 0.1 to sleep 0.1 sec per 100 SCANS\n");
    printf("# in order to reduce server load (usually not needed).\n\n");

    do {
        /* Grab some keys with SCAN */
        reply1 = redisCommand(context, "SCAN %d", it);
        if(reply1 == NULL) {
            fprintf(stderr, "\nI/O error\n");
            exit(1);
        } else if(reply1->type == REDIS_REPLY_ERROR) {
            fprintf(stderr, "SCAN error: %s\n", reply1->str);
            exit(1);
        } else if(reply1->type != REDIS_REPLY_ARRAY) {
            fprintf(stderr, "Non ARRAY response from SCAN!\n");
            exit(1);
        } else if(reply1->elements!=2) {
            fprintf(stderr, "Invalid SCAN result!\n");
            exit(1);
        }
       
        /* Validate the SCAN response */
        assert(reply1->element[0]->type == REDIS_REPLY_STRING);
        assert(reply1->element[1]->type == REDIS_REPLY_ARRAY);

        /* Update iterator and grab pointer to keys */
        it = atoi(reply1->element[0]->str);
        keys = reply1->element[1];

        /* Iterate keys that SCAN returned */
        for(i=0;i<keys->elements;i++) {
            /* Make sure we've got a string, grab it, and increment samples */
            assert(keys->element[i]->type == REDIS_REPLY_STRING);
            key = keys->element[i]->str;
            samples++;

            /* Get the key type */
            reply2 = redisCommand(context, "TYPE %s", key);
            assert(reply2 && reply2->type == REDIS_REPLY_STATUS);

            /* Get the key "size" */
            if (!strcmp(reply2->str,"string")) {
                sizecmd = "STRLEN";
                type = TYPE_STRING;
            } else if (!strcmp(reply2->str,"list")) {
                sizecmd = "LLEN";
                type = TYPE_LIST;
            } else if (!strcmp(reply2->str,"set")) {
                sizecmd = "SCARD";
                type = TYPE_SET;
            } else if (!strcmp(reply2->str,"hash")) {
                sizecmd = "HLEN";
                type = TYPE_HASH;
            } else if (!strcmp(reply2->str,"zset")) {
                sizecmd = "ZCARD";
                type = TYPE_ZSET;
            } else if (!strcmp(reply2->str,"none")) {
                freeReplyObject(reply1);
                freeReplyObject(reply2);
                continue;
            } else {
                fprintf(stderr, "Unknown key type '%s' for key '%s'\n",
                    reply2->str, key);
                exit(1);
            }
            
            /* The size command */
            reply3 = redisCommand(context,"%s %s", sizecmd, key);
            if (reply3 && reply3->type == REDIS_REPLY_INTEGER) {
                if (biggest[type] < reply3->integer) {
                    printf("Biggest %-6s found so far '%s' with %llu %s.\n",
                        typename[type], key,
                        (unsigned long long) reply3->integer,
                        typeunit[type]);
                    biggest[type] = reply3->integer;
                }
            }

            freeReplyObject(reply2);
            if(reply3) freeReplyObject(reply3);
        }

        if (samples && (samples % 1000000) == 0)
            printf("(%llu keys sampled)\n", samples);

        if (samples && (samples % 100) == 0 && config.interval)
            usleep(config.interval);

        freeReplyObject(reply1);
    } while(it != 0);

    /* We've finished scanning the keyspace */
    printf("\n# Scanned all %llu keys in the keyspace!\n", samples);
    exit(0);
}