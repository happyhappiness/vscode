int h2_mplx_shutdown(h2_mplx *m)
{
    int max_stream_started = 0;
    
    H2_MPLX_ENTER(m);

    max_stream_started = m->max_stream_started;
    /* Clear schedule queue, disabling existing streams from starting */ 
    h2_iq_clear(m->q);

    H2_MPLX_LEAVE(m);
    return max_stream_started;
}