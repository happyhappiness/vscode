static size_t used_memory = 0;

static void zmalloc_oom(size_t size) {
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %lu bytes\n",
        size);
    fflush(stderr);
    abort();
