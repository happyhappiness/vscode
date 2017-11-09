int h2_mplx_has_master_events(h2_mplx *m)
{
    return apr_atomic_read32(&m->event_pending) > 0;
}