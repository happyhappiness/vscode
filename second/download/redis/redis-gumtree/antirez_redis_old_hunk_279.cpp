    NULL
};

/* dict-benchmark [count] */
int main(int argc, char **argv) {
    long j;
    long hits = 0, misses = 0;
    long long start, elapsed;
    dict *dict = dictCreate(&BenchmarkDictType,NULL);
    long count = 0;
