static APR_INLINE apr_thread_mutex_t *mutex_hash(volatile apr_uint32_t *mem)
{
    apr_thread_mutex_t *mutex = hash_mutex[ATOMIC_HASH(mem)];

    if (apr_thread_mutex_lock(mutex) != APR_SUCCESS) {
        abort();
    }

    return mutex;
}