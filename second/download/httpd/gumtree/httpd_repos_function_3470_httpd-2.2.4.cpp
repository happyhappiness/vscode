void apr_atomic_sub32(volatile apr_uint32_t *mem, apr_uint32_t val) 
{
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
       
    CHECK(apr_thread_mutex_lock(lock));
    *mem -= val;
    CHECK(apr_thread_mutex_unlock(lock));
#else
    *mem -= val;
#endif /* APR_HAS_THREADS */
}