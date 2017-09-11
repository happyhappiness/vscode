    dictRelease(d);

    d = dictCreate(&dictTypeTest,NULL);
    printf("Getkeys stress test\n");

    for (i = 0; i < MAX2; i++) {
        dictAdd(d,(void*)i,NULL);
        stressGetKeys(d,100);
    }

    for (i = 0; i < MAX2; i++) {
        dictDelete(d,(void*)i);
        dictResize(d);
        stressGetKeys(d,100);
    }
    dictRelease(d);

    printf("TEST PASSED!\n");
