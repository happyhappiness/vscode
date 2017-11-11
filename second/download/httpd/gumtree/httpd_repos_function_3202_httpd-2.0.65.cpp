void apr_atomic_inc(volatile apr_uint32_t *mem) 
{
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t prev;

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        prev = *mem;
        (*mem)++;
        apr_thread_mutex_unlock(lock);
    }
#else
    (*mem)++;
#endif /* APR_HAS_THREADS */
}