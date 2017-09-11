    while (cliReadReply(0) == REDIS_OK);
}

#define TYPE_STRING 0
#define TYPE_LIST   1
#define TYPE_SET    2
#define TYPE_HASH   3
#define TYPE_ZSET   4

static void findBigKeys(void) {
    unsigned long long biggest[5] = {0,0,0,0,0};
    unsigned long long samples = 0;
    redisReply *reply1, *reply2, *reply3;
    char *sizecmd, *typename[] = {"string","list","set","hash","zset"};
    int type;

    printf("\n# Press ctrl+c when you have had enough of it... :)\n");
    printf("# You can use -i 0.1 to sleep 0.1 sec every 100 sampled keys\n");
    printf("# in order to reduce server load (usually not needed).\n\n");
    while(1) {
        /* Sample with RANDOMKEY */
        reply1 = redisCommand(context,"RANDOMKEY");
        if (reply1 == NULL) {
            fprintf(stderr,"\nI/O error\n");
            exit(1);
        } else if (reply1->type == REDIS_REPLY_ERROR) {
            fprintf(stderr, "RANDOMKEY error: %s\n",
                reply1->str);
            exit(1);
        }
        /* Get the key type */
        reply2 = redisCommand(context,"TYPE %s",reply1->str);
        assert(reply2 && reply2->type == REDIS_REPLY_STATUS);
        samples++;

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
            freeReplyObject(reply3);
            continue;
        } else {
            fprintf(stderr, "Unknown key type '%s' for key '%s'\n",
                reply2->str, reply1->str);
            exit(1);
        }

        reply3 = redisCommand(context,"%s %s", sizecmd, reply1->str);
        if (reply3 && reply3->type == REDIS_REPLY_INTEGER) {
            if (biggest[type] < reply3->integer) {
                printf("Biggest %s so far: %s, size: %llu\n",
                    typename[type], reply1->str,
                    (unsigned long long) reply3->integer);
                biggest[type] = reply3->integer;
            }
        }

        if ((samples % 1000000) == 0)
            printf("(%llu keys sampled)\n", samples);

        if ((samples % 100) == 0 && config.interval)
            usleep(config.interval);

        freeReplyObject(reply1);
        freeReplyObject(reply2);
        if (reply3) freeReplyObject(reply3);
    }
}

int main(int argc, char **argv) {
    int firstarg;

