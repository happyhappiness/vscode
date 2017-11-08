int apr_atomic_dec(volatile apr_atomic_t *mem) 
{
#if APR_HAS_THREADS
    apr_thread_mutex_t *lock = hash_mutex[ATOMIC_HASH(mem)];
    apr_uint32_t new;

    if (apr_thread_mutex_lock(lock) == APR_SUCCESS) {
        (*mem)--;
        new = *mem;
        apr_thread_mutex_unlock(lock);
        return new; 
    }
#else
    (*mem)--;
#endif /* APR_HAS_THREADS */
    return *mem; 
}