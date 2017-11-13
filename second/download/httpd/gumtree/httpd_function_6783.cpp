apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
{
    apr_status_t status;
    int acquired;

    /* How to shut down a h2 connection:
     * 1. tell the workers that no more tasks will come from us */
    h2_workers_unregister(m->workers, m);
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        int i, wait_secs = 60;

        /* 2. disable WINDOW_UPDATEs and set the mplx to aborted, clear
         *    our TODO list and purge any streams we have collected */
        h2_mplx_set_consumed_cb(m, NULL, NULL);
        h2_mplx_abort(m);
        h2_iq_clear(m->q);
        purge_streams(m);

        /* 3. wakeup all sleeping tasks. Mark all still active streams as 'done'. 
         *    m->streams has to be empty afterwards with streams either in
         *    a) m->shold because a task is still active
         *    b) m->spurge because task is done, or was not started */
        h2_ihash_iter(m->tasks, task_abort_connection, m);
        apr_thread_cond_broadcast(m->task_thawed);
        while (!h2_ihash_iter(m->streams, stream_done_iter, m)) {
            /* iterate until all streams have been removed */
        }
        ap_assert(h2_ihash_empty(m->streams));

        /* 4. purge all streams we collected by marking them 'done' */
        purge_streams(m);
        
        /* 5. while workers are busy on this connection, meaning they
         *    are processing tasks from this connection, wait on them finishing
         *    to wake us and check again. Eventually, this has to succeed. */    
        m->join_wait = wait;
        for (i = 0; m->workers_busy > 0; ++i) {
            status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
            
            if (APR_STATUS_IS_TIMEUP(status)) {
                /* This can happen if we have very long running requests
                 * that do not time out on IO. */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03198)
                              "h2_mplx(%ld): release, waiting for %d seconds now for "
                              "%d h2_workers to return, have still %d tasks outstanding", 
                              m->id, i*wait_secs, m->workers_busy,
                              (int)h2_ihash_count(m->tasks));
                h2_ihash_iter(m->shold, report_stream_iter, m);
                h2_ihash_iter(m->tasks, task_print, m);
            }
            purge_streams(m);
        }
        m->join_wait = NULL;
        
        /* 6. All workers for this connection are done, we are in 
         * single-threaded processing now effectively. */
        leave_mutex(m, acquired);

        if (!h2_ihash_empty(m->tasks)) {
            /* when we are here, we lost track of the tasks still present.
             * this currently happens with mod_proxy_http2 when we shut
             * down a h2_req_engine with tasks assigned. Since no parallel
             * processing is going on any more, we just clean them up. */ 
            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,  APLOGNO(03056)
                          "h2_mplx(%ld): 3. release_join with %d tasks",
                          m->id, (int)h2_ihash_count(m->tasks));
            h2_ihash_iter(m->tasks, task_print, m);
            
            while (!h2_ihash_iter(m->tasks, task_done_iter, m)) {
                /* iterate until all tasks have been removed */
            }
        }

        /* 7. With all tasks done, the stream hold should be empty and all
         *    remaining streams are ready for purging */
        ap_assert(h2_ihash_empty(m->shold));
        purge_streams(m);
        
        /* 8. close the h2_req_enginge shed and self destruct */
        h2_ngn_shed_destroy(m->ngn_shed);
        m->ngn_shed = NULL;
        h2_mplx_destroy(m);
    }
    return status;
}