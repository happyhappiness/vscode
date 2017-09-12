int main(int argc, char **argv) {
    long j;
    long hits = 0, misses = 0;
    long long start, elapsed;
    dict *dict = dictCreate(&BenchmarkDictType,NULL);
    long count = 0;

    if (argc == 2) {
        count = strtol(argv[1],NULL,10);
    } else {
        count = 5000000;
    }

    start = timeInMilliseconds();
    for (j = 0; j < count; j++) {
        int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
        assert(retval == DICT_OK);
    }
    elapsed = timeInMilliseconds()-start;
    printf("Inserting 5M items: %lld ms\n", elapsed);
    assert((long)dictSize(dict) == count);
}