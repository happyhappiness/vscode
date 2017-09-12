void pfselftestCommand(redisClient *c) {
    int j, i;
    sds bitcounters = sdsnewlen(NULL,REDIS_HLL_SIZE);
    uint8_t bytecounters[REDIS_HLL_REGISTERS];

    /* Test 1: access registers.
     * The test is conceived to test that the different counters of our data
     * structure are accessible and that setting their values both result in
     * the correct value to be retained and not affect adjacent values. */
    for (j = 0; j < REDIS_HLL_TEST_CYCLES; j++) {
        /* Set the HLL counters and an array of unsigned byes of the
         * same size to the same set of random values. */
        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
            unsigned int r = rand() & REDIS_HLL_REGISTER_MAX;

            bytecounters[i] = r;
            HLL_SET_REGISTER(bitcounters,i,r);
        }
        /* Check that we are able to retrieve the same values. */
        for (i = 0; i < REDIS_HLL_REGISTERS; i++) {
            unsigned int val;

            HLL_GET_REGISTER(val,bitcounters,i);
            if (val != bytecounters[i]) {
                addReplyErrorFormat(c,
                    "TESTFAILED Register %d should be %d but is %d",
                    i, (int) bytecounters[i], (int) val);
                goto cleanup;
            }
        }
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
                             (int64_t)hllCount((uint8_t*)bitcounters)