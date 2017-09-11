/* PFSELFTEST
 * This command performs a self-test of the HLL registers implementation.
 * Something that is not easy to test from within the outside. */
#define REDIS_HLL_TEST_CYCLES 1000
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
