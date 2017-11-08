int apr_atomic_dec32(volatile apr_uint32_t *mem) 
{
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t new;

    CHECK(apr_thread_mutex_lock(lock));
    (*mem)--;
    new = *mem;
    CHECK(apr_thread_mutex_unlock(lock));
    return new;
#else
    (*mem)--;
    return *mem; 
#endif /* APR_HAS_THREADS */
}