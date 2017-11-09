void h2_beam_mutex_set(h2_bucket_beam *beam, 
                       h2_beam_mutex_enter m_enter,
                       void *m_ctx)
{
    h2_beam_lock bl;
    
    if (enter_yellow(beam, &bl) == APR_SUCCESS) {
        beam->m_enter = m_enter;
        beam->m_ctx   = m_ctx;
        leave_yellow(beam, &bl);
    }
}