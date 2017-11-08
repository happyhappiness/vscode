apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    workers_unregister(m);

    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        int attempts = 0;
        
        release(m);
        while (apr_atomic_read32(&m->refs) > 0) {
            m->join_wait = wait;
            ap_log_cerror(APLOG_MARK, (attempts? APLOG_INFO : APLOG_DEBUG), 
                          0, m->c,
                          "h2_mplx(%ld): release_join, refs=%d, waiting...", 
                          m->id, m->refs);
            apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(10));
            if (++attempts >= 6) {
                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
                              APLOGNO(02952) 
                              "h2_mplx(%ld): join attempts exhausted, refs=%d", 
                              m->id, m->refs);
                break;
            }
        }
        if (m->join_wait) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                          "h2_mplx(%ld): release_join -> destroy", m->id);
        }
        m->join_wait = NULL;
        apr_thread_mutex_unlock(m->lock);
        h2_mplx_destroy(m);
    }
    return status;
}