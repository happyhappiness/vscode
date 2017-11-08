apr_uint32_t apr_atomic_cas(volatile apr_uint32_t *mem, long with, long cmp)
{
    long prev;
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *(long*)mem;
        if (prev == cmp) {
            *(long*)mem = with;
        }
        apr_thread_mutex_unlock(lock);
        return prev;
    }
    return *(long*)mem;
#else
    prev = *(long*)mem;
    if (prev == cmp) {
        *(long*)mem = with;
    }
    return prev;
#endif /* APR_HAS_THREADS */
}