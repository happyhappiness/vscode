void h2_beam_mutex_set(h2_bucket_beam *beam, 
                       h2_beam_mutex_enter m_enter,
                       apr_thread_cond_t *cond,
                       void *m_ctx)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->m_enter = m_enter;
        beam->m_ctx   = m_ctx;
        beam->m_cond  = cond;
        leave_yellow(beam, &bl);
    }
}