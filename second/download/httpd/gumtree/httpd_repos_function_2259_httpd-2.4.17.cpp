static void release(h2_mplx *m)
{
    if (!apr_atomic_dec32(&m->refs)) {
        if (m->join_wait) {
            apr_thread_cond_signal(m->join_wait);
        }
    }
}