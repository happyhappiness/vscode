    while (cliReadReply(0) == REDIS_OK);
}

#define TYPE_STRING 0
#define TYPE_LIST   1
#define TYPE_SET    2
