apr_uint32_t apr_atomic_xchg32(volatile apr_uint32_t *mem, apr_uint32_t val)
{
    apr_uint32_t prev;
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];

    CHECK(apr_thread_mutex_lock(lock));
    prev = *mem;
    *mem = val;
    CHECK(apr_thread_mutex_unlock(lock));
#else
    prev = *mem;
    *mem = val;
#endif /* APR_HAS_THREADS */
    return prev;
}