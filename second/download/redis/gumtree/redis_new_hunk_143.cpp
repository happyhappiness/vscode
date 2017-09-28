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
