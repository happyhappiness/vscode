void h2_mplx_reference(h2_mplx *m)
{
    apr_thread_mutex_lock(m->lock);
    ++m->refs;
    apr_thread_mutex_unlock(m->lock);
}