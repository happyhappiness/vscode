static size_t used_memory = 0;
static int zmalloc_thread_safe = 0;
pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;
/* Note that malloc_allocations elements are initialized to zero by C */
size_t zmalloc_allocations[ZMALLOC_MAX_ALLOC_STAT+1];

static void zmalloc_oom(size_t size) {
    fprintf(stderr, "zmalloc: Out of memory trying to allocate %zu bytes\n",
