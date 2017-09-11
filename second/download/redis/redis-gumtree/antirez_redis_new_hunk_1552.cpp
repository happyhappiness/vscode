    dictRelease(d);

    d = dictCreate(&dictTypeTest,NULL);

    printf("Stress testing dictGetSomeKeys\n");
    int perfect_run = 0, approx_run = 0;

    for (i = 0; i < MAX2; i++) {
        dictAdd(d,(void*)i,NULL);
        stressGetKeys(d,100,&perfect_run,&approx_run);
    }

    for (i = 0; i < MAX2; i++) {
        dictDelete(d,(void*)i);
        dictResize(d);
        stressGetKeys(d,100,&perfect_run,&approx_run);
    }

    printf("dictGetSomeKey, %d perfect runs, %d approximated runs\n",
        perfect_run, approx_run);

    dictRelease(d);

    printf("TEST PASSED!\n");
