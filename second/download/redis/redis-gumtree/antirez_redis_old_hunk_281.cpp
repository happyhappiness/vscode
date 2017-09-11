    NULL
};

int main(void) {
    long j;
    long hits = 0, misses = 0;
    long long start, elapsed;
    dict *dict = dictCreate(&BenchmarkDictType,NULL);

    start = timeInMilliseconds();
    for (j = 0; j < 5000000; j++) {
        int retval = dictAdd(dict,sdsfromlonglong(j),(void*)j);
        assert(retval == DICT_OK);
    }
    elapsed = timeInMilliseconds()-start;
    printf("Inserting 5M items: %lld ms\n", elapsed);
    assert(dictSize(dict) == 5000000);
}
#endif
