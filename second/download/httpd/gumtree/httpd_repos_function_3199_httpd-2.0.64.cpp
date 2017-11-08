void *apr_atomic_casptr(volatile void **mem, void *with, const void *cmp)
{
    void *prev;
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *(void **)mem;
        if (prev == cmp) {
            *mem = with;
        }
        apr_thread_mutex_unlock(lock);
        return prev;
    }
    return *(void **)mem;
#else
    prev = *(void **)mem;
    if (prev == cmp) {
        *mem = with;
    }
    return prev;
#endif /* APR_HAS_THREADS */
}