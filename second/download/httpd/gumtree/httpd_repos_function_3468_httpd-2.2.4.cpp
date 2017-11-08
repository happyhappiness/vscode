apr_uint32_t apr_atomic_add32(volatile apr_uint32_t *mem, apr_uint32_t val)
{
    apr_uint32_t old_value;

#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
       
    CHECK(apr_thread_mutex_lock(lock));
    old_value = *mem;
    *mem += val;
    CHECK(apr_thread_mutex_unlock(lock));
#else
    old_value = *mem;
    *mem += val;
#endif /* APR_HAS_THREADS */
    return old_value;
}