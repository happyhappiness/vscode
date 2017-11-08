static apr_status_t wait_cond(h2_bucket_beam *beam, apr_thread_mutex_t *lock)
{
    if (beam->timeout > 0) {
        return apr_thread_cond_timedwait(beam->m_cond, lock, beam->timeout);
    }
    else {
        return apr_thread_cond_wait(beam->m_cond, lock);
    }
}