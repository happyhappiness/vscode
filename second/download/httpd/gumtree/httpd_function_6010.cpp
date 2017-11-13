apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    
    workers_unregister(m);
    status = apr_thread_mutex_lock(m->lock);
    if (APR_SUCCESS == status) {
        while (!h2_io_set_iter(m->stream_ios, stream_done_iter, m)) {
            /* iterator until all h2_io have been orphaned or destroyed */
        }
    
        release(m, 0);
        while (m->refs > 0) {
            m->join_wait = wait;
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                          "h2_mplx(%ld): release_join, refs=%d, waiting...", 
                          m->id, m->refs);
            apr_thread_cond_wait(wait, m->lock);
        }
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
                      "h2_mplx(%ld): release_join -> destroy, (#ios=%ld)", 
                      m->id, (long)h2_io_set_size(m->stream_ios));
        h2_mplx_destroy(m);
        /* all gone */
        /*apr_thread_mutex_unlock(m->lock);*/
    }
    return status;
}