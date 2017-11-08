static apr_status_t beam_enter(void *ctx, h2_beam_lock *pbl)
{
    h2_mplx *m = ctx;
    int acquired;
    apr_status_t status;
    
    status = enter_mutex(m, &acquired);
    if (status == APR_SUCCESS) {
        pbl->mutex = m->lock;
        pbl->leave = acquired? beam_leave : NULL;
        pbl->leave_ctx = m;
    }
    return status;
}