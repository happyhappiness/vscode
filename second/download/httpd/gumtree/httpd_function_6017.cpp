apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int acquired;

    h2_workers_unregister(m->workers, m);
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int i, wait_secs = 5;
        
        /* disable WINDOW_UPDATE callbacks */
        h2_mplx_set_consumed_cb(m, NULL, NULL);
        
        h2_iq_clear(m->q);
        apr_thread_cond_broadcast(m->task_thawed);
        while (!h2_io_set_iter(m->stream_ios, stream_done_iter, m)) {
            /* iterate until all ios have been orphaned or destroyed */
        }
    
        /* If we still have busy workers, we cannot release our memory
         * pool yet, as slave connections have child pools of their respective
         * h2_io's.
         * Any remaining ios are processed in these workers. Any operation 
         * they do on their input/outputs will be errored ECONNRESET/ABORTED, 
         * so processing them should fail and workers *should* return.
         */
        for (i = 0; m->workers_busy > 0; ++i) {
            m->join_wait = wait;
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): release_join, waiting on %d worker to report back", 
                          m->id, (int)h2_io_set_size(m->stream_ios));
                          
            status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
            if (APR_STATUS_IS_TIMEUP(status)) {
                if (i > 0) {
                    /* Oh, oh. Still we wait for assigned  workers to report that 
                     * they are done. Unless we have a bug, a worker seems to be hanging. 
                     * If we exit now, all will be deallocated and the worker, once 
                     * it does return, will walk all over freed memory...
                     */
                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03198)
                                  "h2_mplx(%ld): release, waiting for %d seconds now for "
                                  "%d h2_workers to return, have still %d requests outstanding", 
                                  m->id, i*wait_secs, m->workers_busy,
                                  (int)h2_io_set_size(m->stream_ios));
                    if (i == 1) {
                        h2_io_set_iter(m->stream_ios, stream_print, m);
                    }
                }
                h2_mplx_abort(m);
                apr_thread_cond_broadcast(m->task_thawed);
            }
        }
        
        if (!h2_io_set_is_empty(m->stream_ios)) {
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, 
                          "h2_mplx(%ld): release_join, %d streams still open", 
                          m->id, (int)h2_io_set_size(m->stream_ios));
        }
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03056)
                      "h2_mplx(%ld): release_join -> destroy", m->id);
        leave_mutex(m, acquired);
        h2_mplx_destroy(m);
        /* all gone */
    }
    return status;
}