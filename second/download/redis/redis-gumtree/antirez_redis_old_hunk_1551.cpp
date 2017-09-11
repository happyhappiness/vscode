    return la-lb;
}

void stressGetKeys(dict *d, int times) {
    int j;
    dictEntry **des = zmalloc(sizeof(dictEntry*)*dictSize(d));
    for (j = 0; j < times; j++) {
        int requested = rand() % (dictSize(d)+1);
        int returned = dictGetSomeKeys(d, des, requested);
        if (requested != returned) {
            printf("*** ERROR! Req: %d, Ret: %d\n", requested, returned);
            exit(1);
        }
        qsort(des,returned,sizeof(dictEntry*),sortPointers);
        if (returned > 1) {
            int i;
            for (i = 0; i < returned-1; i++) {
                if (des[i] == des[i+1]) {
                    printf("*** ERROR! Duplicated element detected\n");
                    exit(1);
                }
            }
        }
    }
    zfree(des);
}
