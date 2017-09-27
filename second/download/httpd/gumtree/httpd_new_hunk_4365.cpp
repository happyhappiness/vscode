        
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
        leave_mutex(m, acquired);
    }
    return status;
}
 
void h2_mplx_req_engine_done(h2_req_engine *ngn, conn_rec *r_conn,
                             apr_status_t status)
{
    h2_task *task = h2_ctx_cget_task(r_conn);
    
    if (task) {
        h2_mplx *m = task->mplx;
        int acquired;

        if (enter_mutex(m, &acquired) == APR_SUCCESS) {
            ngn_out_update_windows(m, ngn);
            h2_ngn_shed_done_task(m->ngn_shed, ngn, task);
            if (status != APR_SUCCESS && h2_task_can_redo(task) 
                && !h2_ihash_get(m->redo_tasks, task->stream_id)) {
                h2_ihash_add(m->redo_tasks, task);
            }
            if (task->engine) { 
                /* cannot report that as done until engine returns */
            }
            else {
                task_done(m, task, ngn);
            }
