    }

    /* Test 2: approximation error.
     * The test is adds unique elements and check that the estimated value
     * is always reasonable bounds.
     * 
     * We check that the error is smaller than 4 times than the expected
     * standard error, to make it very unlikely for the test to fail because
     * of a "bad" run. */
    memset(bitcounters,0,REDIS_HLL_SIZE);
    double relerr = 1.04/sqrt(REDIS_HLL_REGISTERS);
    int64_t checkpoint = 1000;
    uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
    uint64_t ele;
    for (j = 1; j <= 10000000; j++) {
        ele = j ^ seed;
        hllAdd((uint8_t*)bitcounters,(unsigned char*)&ele,sizeof(ele));
        if (j == checkpoint) {
            int64_t abserr = checkpoint-
                             (int64_t)hllCount((uint8_t*)bitcounters);
            if (abserr < 0) abserr = -abserr;
            if (abserr > (uint64_t)(relerr*4*checkpoint)) {
                addReplyErrorFormat(c,
