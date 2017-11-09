apr_status_t h2_mplx_req_engine_pull(h2_req_engine *ngn, 
                                     apr_read_type_e block, 
                                     int capacity, 
                                     request_rec **pr)
{   
    h2_ngn_shed *shed = h2_ngn_shed_get_shed(ngn);
    h2_mplx *m = h2_ngn_shed_get_ctx(shed);
    apr_status_t status;
    int want_shutdown;
    
    H2_MPLX_ENTER(m);

    want_shutdown = (block == APR_BLOCK_READ);

    /* Take this opportunity to update output consummation 
     * for this engine */
    ngn_out_update_windows(m, ngn);
    
    if (want_shutdown && !h2_iq_empty(m->q)) {
        /* For a blocking read, check first if requests are to be
         * had and, if not, wait a short while before doing the
         * blocking, and if unsuccessful, terminating read.
         */
        status = h2_ngn_shed_pull_request(shed, ngn, capacity, 1, pr);
        if (APR_STATUS_IS_EAGAIN(status)) {
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          "h2_mplx(%ld): start block engine pull", m->id);
            apr_thread_cond_timedwait(m->task_thawed, m->lock, 
                                      apr_time_from_msec(20));
            status = h2_ngn_shed_pull_request(shed, ngn, capacity, 1, pr);
        }
    }
    else {
        status = h2_ngn_shed_pull_request(shed, ngn, capacity,
                                          want_shutdown, pr);
    }

    H2_MPLX_LEAVE(m);
    return status;
}