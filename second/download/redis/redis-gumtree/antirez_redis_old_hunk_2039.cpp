    }

    /* Test 2: approximation error.
     * The test is adds unique elements and check that the estimated value
     * is always reasonable bounds.
     * 
     * We check that the error is smaller than 4 times than the expected
     * standard error, to make it very unlikely for the test to fail because
     * of a "bad" run. */
    memset(hdr->registers,0,HLL_DENSE_SIZE-HLL_HDR_SIZE);
    double relerr = 1.04/sqrt(HLL_REGISTERS);
    int64_t checkpoint = 1000;
    uint64_t seed = (uint64_t)rand() | (uint64_t)rand() << 32;
    uint64_t ele;
    for (j = 1; j <= 10000000; j++) {
        ele = j ^ seed;
        hllDenseAdd(hdr->registers,(unsigned char*)&ele,sizeof(ele));
        if (j == checkpoint) {
            int64_t abserr = checkpoint - (int64_t)hllCount(hdr,NULL);
            if (abserr < 0) abserr = -abserr;
