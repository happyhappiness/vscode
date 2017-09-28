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
