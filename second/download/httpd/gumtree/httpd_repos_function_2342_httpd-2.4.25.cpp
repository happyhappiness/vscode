static void beam_leave(void *ctx, apr_thread_mutex_t *lock)
{
    leave_mutex(ctx, 1);
}