static apr_status_t enter_yellow(h2_bucket_beam *beam, h2_beam_lock *pbl)
{
    h2_beam_mutex_enter *enter = beam->m_enter;
    if (enter) {
        void *ctx = beam->m_ctx;
        if (ctx) {
            return enter(ctx, pbl);
        }
    }
    pbl->mutex = NULL;
    pbl->leave = NULL;
    return APR_SUCCESS;
}