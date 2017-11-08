apr_status_t h2_mplx_req_engine_push(const char *ngn_type, 
                                     request_rec *r,
                                     http2_req_engine_init *einit)
{
    apr_status_t status;
    h2_mplx *m;
    h2_task *task;
    int acquired;
    
    task = h2_ctx_rget_task(r);
    if (!task) {
        return APR_ECONNABORTED;
    }
    m = task->mplx;
    task->r = r;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_io *io = h2_io_set_get(m->stream_ios, task->stream_id);
        if (!io || io->orphaned) {
            status = APR_ECONNABORTED;
        }
        else {
            status = h2_ngn_shed_push_task(m->ngn_shed, ngn_type, task, einit);
        }
        leave_mutex(m, acquired);
    }
    return status;
}