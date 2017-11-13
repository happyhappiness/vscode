apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int acquired;

    h2_workers_unregister(m->workers, m);
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int i, wait_secs = 5;

        if (!h2_ihash_empty(m->streams) && APLOGctrace1(m->c)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): release_join with %d streams open, "
                          "%d streams resume, %d streams ready, %d tasks", 
                          m->id, (int)h2_ihash_count(m->streams),
                          (int)h2_ihash_count(m->sresume), 
                          (int)h2_ihash_count(m->sready), 
                          (int)h2_ihash_count(m->tasks));
            h2_ihash_iter(m->streams, report_stream_iter, m);
        }
        
        /* disable WINDOW_UPDATE callbacks */
        h2_mplx_set_consumed_cb(m, NULL, NULL);
        
        if (!h2_ihash_empty(m->shold)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): start release_join with %d streams in hold", 
                          m->id, (int)h2_ihash_count(m->shold));
        }
        if (!h2_ihash_empty(m->spurge)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): start release_join with %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));
        }
        
        h2_iq_clear(m->q);
        apr_thread_cond_broadcast(m->task_thawed);
        while (!h2_ihash_iter(m->streams, stream_done_iter, m)) {
            /* iterate until all streams have been removed */
        }
        AP_DEBUG_ASSERT(h2_ihash_empty(m->streams));
    
        if (!h2_ihash_empty(m->shold)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 2. release_join with %d streams in hold", 
                          m->id, (int)h2_ihash_count(m->shold));
        }
        if (!h2_ihash_empty(m->spurge)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 2. release_join with %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));
        }
        
        /* If we still have busy workers, we cannot release our memory
         * pool yet, as tasks have references to us.
         * Any operation on the task slave connection will from now on
         * be errored ECONNRESET/ABORTED, so processing them should fail 
         * and workers *should* return in a timely fashion.
         */
        for (i = 0; m->workers_busy > 0; ++i) {
            h2_ihash_iter(m->tasks, task_abort_connection, m);
            
            m->join_wait = wait;
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
                                  "%d h2_workers to return, have still %d tasks outstanding", 
                                  m->id, i*wait_secs, m->workers_busy,
                                  (int)h2_ihash_count(m->tasks));
                    if (i == 1) {
                        h2_ihash_iter(m->tasks, task_print, m);
                    }
                }
                h2_mplx_abort(m);
                apr_thread_cond_broadcast(m->task_thawed);
            }
        }
        
        AP_DEBUG_ASSERT(h2_ihash_empty(m->shold));
        if (!h2_ihash_empty(m->spurge)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
                          "h2_mplx(%ld): 3. release_join %d streams to purge", 
                          m->id, (int)h2_ihash_count(m->spurge));
            purge_streams(m);
        }
        AP_DEBUG_ASSERT(h2_ihash_empty(m->spurge));
        
        if (!h2_ihash_empty(m->tasks)) {
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03056)
                          "h2_mplx(%ld): release_join -> destroy, "
                          "%d tasks still present", 
                          m->id, (int)h2_ihash_count(m->tasks));
        }
        leave_mutex(m, acquired);
        h2_mplx_destroy(m);
        /* all gone */
    }
    return status;
}