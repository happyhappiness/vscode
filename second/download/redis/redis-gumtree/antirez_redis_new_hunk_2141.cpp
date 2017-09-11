#define TYPE_SET    2
#define TYPE_HASH   3
#define TYPE_ZSET   4
#define TYPE_NONE   5

static redisReply *sendScan(unsigned long long *it) {
    redisReply *reply = redisCommand(context, "SCAN %llu", *it);

    /* Handle any error conditions */
    if(reply == NULL) {
        fprintf(stderr, "\nI/O error\n");
        exit(1);
    } else if(reply->type == REDIS_REPLY_ERROR) {
        fprintf(stderr, "SCAN error: %s\n", reply->str);
        exit(1);
    } else if(reply->type != REDIS_REPLY_ARRAY) {
        fprintf(stderr, "Non ARRAY response from SCAN!\n");
        exit(1);
    } else if(reply->elements != 2) {
        fprintf(stderr, "Invalid element count from SCAN!\n");
        exit(1);
    }

    /* Validate our types are correct */
    assert(reply->element[0]->type == REDIS_REPLY_STRING);
    assert(reply->element[1]->type == REDIS_REPLY_ARRAY);
    
    /* Update iterator */
    *it = atoi(reply->element[0]->str);

    return reply;
}

static int getDbSize(void) {
    redisReply *reply;
    int size;

    reply = redisCommand(context, "DBSIZE");
    
    if(reply == NULL || reply->type != REDIS_REPLY_INTEGER) {
        fprintf(stderr, "Couldn't determine DBSIZE!\n");
        exit(1);
    }

    /* Grab the number of keys and free our reply */
    size = reply->integer;
    freeReplyObject(reply);

    return size;
}

static int toIntType(char *key, char *type) {
    if(!strcmp(type, "string")) {
        return TYPE_STRING;
    } else if(!strcmp(type, "list")) {
        return TYPE_LIST;
    } else if(!strcmp(type, "set")) {
        return TYPE_SET;
    } else if(!strcmp(type, "hash")) {
        return TYPE_HASH;
    } else if(!strcmp(type, "zset")) {
        return TYPE_ZSET;
    } else if(!strcmp(type, "none")) {
        return TYPE_NONE;
    } else {
        fprintf(stderr, "Unknown type '%s' for key '%s'\n", type, key);
        exit(1);
    }
}

static void getKeyTypes(redisReply *keys, int *types) {
    redisReply *reply;
    int i;

    /* Pipeline TYPE commands */
    for(i=0;i<keys->elements;i++) {
        redisAppendCommand(context, "TYPE %s", keys->element[i]->str);
    }

    /* Retrieve types */
    for(i=0;i<keys->elements;i++) {
        if(redisGetReply(context, (void**)&reply)!=REDIS_OK) {
            fprintf(stderr, "Error getting type for key '%s' (%d: %s)\n",
                keys->element[i]->str, context->err, context->errstr);
            exit(1);
        } else if(reply->type != REDIS_REPLY_STATUS) {
            fprintf(stderr, "Invalid reply type (%d) for TYPE on key '%s'!\n",
                reply->type, keys->element[i]->str);
            exit(1);
        }

        types[i] = toIntType(keys->element[i]->str, reply->str); 
        freeReplyObject(reply);
    }
}

static void getKeySizes(redisReply *keys, int *types, 
                        unsigned long long *sizes) 
{
    redisReply *reply;
    char *sizecmds[] = {"STRLEN","LLEN","SCARD","HLEN","ZCARD"};
    int i;

    /* Pipeline size commands */
    for(i=0;i<keys->elements;i++) {
        /* Skip keys that were deleted */
        if(types[i]==TYPE_NONE) 
            continue;

        redisAppendCommand(context, "%s %s", sizecmds[types[i]], 
            keys->element[i]->str);
    }

    /* Retreive sizes */
    for(i=0;i<keys->elements;i++) {
        /* Skip keys that dissapeared between SCAN and TYPE */
        if(types[i] == TYPE_NONE) {
            sizes[i] = 0;
            continue;
        }

        /* Retreive size */
        if(redisGetReply(context, (void**)&reply)!=REDIS_OK) {
            fprintf(stderr, "Error getting size for key '%s' (%d: %s)\n",
                keys->element[i]->str, context->err, context->errstr);
            exit(1);
        } else if(reply->type != REDIS_REPLY_INTEGER) {
            /* Theoretically the key could have been removed and
             * added as a different type between TYPE and SIZE */
            fprintf(stderr, 
                "Warning:  %s on '%s' failed (may have changed type)\n",
                 sizecmds[types[i]], keys->element[i]->str);
            sizes[i] = 0;
        } else {
            sizes[i] = reply->integer;
        }
            
        freeReplyObject(reply);
    }
}

static void findBigKeys(void) {
    unsigned long long biggest[5] = {0}, counts[5] = {0}, totalsize[5] = {0};
    unsigned long long sampled = 0, total_keys, totlen=0, *sizes=NULL, it=0;
    sds maxkeys[5] = {0};
    char *typename[] = {"string","list","set","hash","zset"};
    char *typeunit[] = {"bytes","items","members","fields","members"};
    redisReply *reply, *keys;
    int type, *types=NULL, arrsize=0, i;
    double pct;

    /* Total keys pre scanning */
    total_keys = getDbSize();

    /* Status message */
    printf("\n# Scanning the entire keyspace to find biggest keys as well as\n");
    printf("# average sizes per key type.  You can use -i 0.1 to sleep 0.1 sec\n");
    printf("# per 100 SCAN commands (not usually needed).\n\n");

    /* New up sds strings to keep track of overall biggest per type */
    for(i=0;i<TYPE_NONE; i++) {
        maxkeys[i] = sdsempty();
        if(!maxkeys[i]) {
            fprintf(stderr, "Failed to allocate memory for largest key names!");
            exit(1);
        }
    }

    /* SCAN loop */
    do {
        /* Calculate approximate percentage completion */
        pct = 100 * (double)sampled/total_keys;

        /* Grab some keys and point to the keys array */
        reply = sendScan(&it);
        keys  = reply->element[1];

        /* Reallocate our type and size array if we need to */
        if(keys->elements > arrsize) {
            types = zrealloc(types, sizeof(int)*keys->elements);
            sizes = zrealloc(sizes, sizeof(unsigned long long)*keys->elements);

            if(!types || !sizes) {
                fprintf(stderr, "Failed to allocate storage for keys!\n");
                exit(1);
            }

            arrsize = keys->elements;
        }

        /* Retreive types and then sizes */
        getKeyTypes(keys, types);
        getKeySizes(keys, types, sizes);
        
        /* Now update our stats */
        for(i=0;i<keys->elements;i++) {
            if((type = types[i]) == TYPE_NONE)
                continue;
            
            totalsize[type] += sizes[i];
            counts[type]++;
            totlen += keys->element[i]->len;
            sampled++;

            if(biggest[type]<sizes[i]) {
                printf(
                   "[%05.2f%%] Biggest %-6s found so far '%s' with %llu %s\n",
                   pct, typename[type], keys->element[i]->str, sizes[i],
                   typeunit[type]);

                /* Keep track of biggest key name for this type */
                maxkeys[type] = sdscpy(maxkeys[type], keys->element[i]->str);
                if(!maxkeys[type]) {
                    fprintf(stderr, "Failed to allocate memory for key!\n");
                    exit(1);
                }

                /* Keep track of the biggest size for this type */
                biggest[type] = sizes[i];                
            }

            /* Update overall progress */
            if(sampled % 1000000 == 0) {
                printf("[%05.2f%%] Sampled %llu keys so far\n", pct, sampled);
            }
        }

        /* Sleep if we've been directed to do so */
        if(sampled && (sampled %100) == 0 && config.interval) {
            usleep(config.interval);
        }
        
        freeReplyObject(reply);
    } while(it != 0);

    if(types) zfree(types);
    if(sizes) zfree(sizes);

    /* We're done */
    printf("\n-------- summary -------\n\n");

    printf("Sampled %llu keys in the keyspace!\n", sampled);
    printf("Total key length in bytes is %llu (avg len %.2f)\n\n",
       totlen, totlen ? (double)totlen/sampled : 0);

    /* Output the biggest keys we found, for types we did find */
    for(i=0;i<TYPE_NONE;i++) {
        if(sdslen(maxkeys[i])>0) {
            printf("Biggest %6s found '%s' has %llu %s\n", typename[i], maxkeys[i],
               biggest[i], typeunit[i]);
        }
    }

    printf("\n");

    for(i=0;i<TYPE_NONE;i++) {
        printf("%llu %ss with %llu %s (%05.2f%% of keys, avg size %.2f)\n",
           counts[i], typename[i], totalsize[i], typeunit[i],
           sampled ? 100 * (double)counts[i]/sampled : 0,
           counts[i] ? (double)totalsize[i]/counts[i] : 0);
    }

    /* Free sds strings containing max keys */
    for(i=0;i<TYPE_NONE;i++) {
        sdsfree(maxkeys[i]);
    }

    /* Success! */
    exit(0);
}

