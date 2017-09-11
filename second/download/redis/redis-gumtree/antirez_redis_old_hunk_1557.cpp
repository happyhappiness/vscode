    dictEntry **des = zmalloc(sizeof(dictEntry*)*dictSize(d));
    for (j = 0; j < times; j++) {
        int requested = rand() % (dictSize(d)+1);
        int returned = dictGetRandomKeys(d, des, requested);
        if (requested != returned) {
            printf("*** ERROR! Req: %d, Ret: %d\n", requested, returned);
            exit(1);
