    unsigned long long samples = 0;
    redisReply *reply1, *reply2, *reply3 = NULL;
    char *sizecmd, *typename[] = {"string","list","set","hash","zset"};
    char *typeunit[] = {"bytes","items","members","fields","members"};
    int type;

    printf("\n# Press ctrl+c when you have had enough of it... :)\n");
