apr_status_t h2_mplx_req_engine_push(const char *ngn_type, 
                                     request_rec *r,
                                     http2_req_engine_init *einit)
{
    apr_status_t status;
    h2_mplx *m;
    h2_task *task;
    h2_stream *stream;
    
    task = h2_ctx_rget_task(r);
    if (!task) {
        return APR_ECONNABORTED;
    }
    m = task->mplx;
    
    H2_MPLX_ENTER(m);

    stream = h2_ihash_get(m->streams, task->stream_id);
    if (stream) {
        status = h2_ngn_shed_push_request(m->ngn_shed, ngn_type, r, einit);
    }
    else {
        status = APR_ECONNABORTED;
    }

    H2_MPLX_LEAVE(m);
    return status;
}