apr_uint32_t apr_atomic_cas(volatile apr_uint32_t *mem, long with, long cmp)
{
    apr_uint32_t prev;
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *mem;
        if (prev == (apr_uint32_t)cmp) {
            *mem = (apr_uint32_t)with;
        }
        apr_thread_mutex_unlock(lock);
        return prev;
    }
    return *mem;
#else
    prev = *mem;
    if (prev == (apr_uint32_t)cmp) {
        *mem = (apr_uint32_t)with;
    }
    return prev;
#endif /* APR_HAS_THREADS */
}