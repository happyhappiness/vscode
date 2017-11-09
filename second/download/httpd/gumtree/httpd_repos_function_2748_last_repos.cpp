static apr_status_t mutex_enter(void *ctx, h2_beam_lock *pbl)
{
    h2_bucket_beam *beam = ctx;
    pbl->mutex = beam->lock;
    pbl->leave = mutex_leave;
    return apr_thread_mutex_lock(pbl->mutex);
}