static void release(h2_mplx *m, int lock)
{
    if (lock) {
        apr_thread_mutex_lock(m->lock);
        --m->refs;
        if (m->join_wait) {
            apr_thread_cond_signal(m->join_wait);
        }
        apr_thread_mutex_unlock(m->lock);
    }
    else {
        --m->refs;
    }
}