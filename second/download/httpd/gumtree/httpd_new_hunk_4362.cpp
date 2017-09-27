                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    int do_registration = 0;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (m->aborted) {
            status = APR_ECONNABORTED;
        }
        else {
            h2_ihash_add(m->streams, stream);
            if (h2_stream_is_ready(stream)) {
                h2_iq_append(m->readyq, stream->id);
            }
            else {
                if (!m->need_registration) {
                    m->need_registration = h2_iq_empty(m->q);
                }
                if (m->workers_busy < m->workers_max) {
                    do_registration = m->need_registration;
                }
                h2_iq_add(m->q, stream->id, cmp, ctx);                
            }
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
                          "h2_mplx(%ld-%d): process", m->c->id, stream->id);
        }
        leave_mutex(m, acquired);
    }
    if (do_registration) {
        m->need_registration = 0;
        h2_workers_register(m->workers, m);
    }
    return status;
}

static h2_task *next_stream_task(h2_mplx *m)
{
    h2_task *task = NULL;
    h2_stream *stream;
    int sid;
    while (!m->aborted && !task  && (m->workers_busy < m->workers_limit)
           && (sid = h2_iq_shift(m->q)) > 0) {
