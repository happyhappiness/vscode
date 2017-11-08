int main(int argc, char **argv)
{
    apr_pool_t *pool;
    apr_status_t rv;
    int i;
    int nTests = sizeof(testRuns) / sizeof(testRuns[0]);
    struct testResult *results;

    printf("APR Test Application: sockperf\n");

    apr_initialize();
    atexit(apr_terminate);

    apr_pool_create(&pool, NULL);

    results = (struct testResult *)apr_pcalloc(pool, 
                                        sizeof(*results) * nTests);

    for(i = 0; i < nTests; i++) {
        printf("Test -> %c\n", testRuns[i].c);
        results[i].size = testRuns[i].size * (apr_size_t)TEST_SIZE;
        rv = runTest(&testRuns[i], &results[i], pool);
    }

    printf("Tests Complete!\n");
    for(i = 0; i < nTests; i++) {
        int j;
        apr_time_t totTime = 0;
        printf("%10d byte block:\n", results[i].size);
        printf("\t%2d iterations : ", results[i].iters);
        for (j = 0; j < results[i].iters; j++) {
            printf("%6" APR_TIME_T_FMT, results[i].msecs[j]);
            totTime += results[i].msecs[j];
        }
        printf("<\n");
        printf("\t  Average: %6" APR_TIME_T_FMT "\n",
               totTime / results[i].iters);
    }

    return 0;
}