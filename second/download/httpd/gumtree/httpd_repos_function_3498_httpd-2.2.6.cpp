void *apr_atomic_casptr(volatile void **mem, void *with, const void *cmp)
{
    void *prev;
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];

    CHECK(apr_thread_mutex_lock(lock));
    prev = *(void **)mem;
    if (prev == cmp) {
        *mem = with;
    }
    CHECK(apr_thread_mutex_unlock(lock));
#else
    prev = *(void **)mem;
    if (prev == cmp) {
        *mem = with;
    }
#endif /* APR_HAS_THREADS */
    return prev;
}