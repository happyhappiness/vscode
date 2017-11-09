void h2_mplx_req_engine_done(h2_req_engine *ngn, conn_rec *r_conn,
                             apr_status_t status)
{
    h2_task *task = h2_ctx_cget_task(r_conn);
    
    if (task) {
        h2_mplx *m = task->mplx;
        h2_stream *stream;

        H2_MPLX_ENTER_ALWAYS(m);

        stream = h2_ihash_get(m->streams, task->stream_id);
        
        ngn_out_update_windows(m, ngn);
        h2_ngn_shed_done_task(m->ngn_shed, ngn, task);
        
        if (status != APR_SUCCESS && stream 
            && h2_task_can_redo(task) 
            && !h2_ihash_get(m->sredo, stream->id)) {
            h2_ihash_add(m->sredo, stream);
        }

        if (task->engine) { 
            /* cannot report that as done until engine returns */
        }
        else {
            task_done(m, task, ngn);
        }

        H2_MPLX_LEAVE(m);
    }
}