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
            /* Take this opportunity to update output consummation 
             * for this engine */
            leave_mutex(m, acquired);
        }
    }
}