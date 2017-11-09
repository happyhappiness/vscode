static void mutex_leave(void *ctx, apr_thread_mutex_t *lock)
{
    apr_thread_mutex_unlock(lock);
}