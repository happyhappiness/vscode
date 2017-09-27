    input_consumed_signal(ctx, val);
    return 1;
}

apr_status_t h2_mplx_dispatch_master_events(h2_mplx *m, 
                                            stream_ev_callback *on_resume, 
                                            void *on_ctx)
{
    apr_status_t status;
    int acquired;
    int ids[100];
    h2_stream *stream;
    size_t i, n;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                      "h2_mplx(%ld): dispatch events", m->id);
                      
        /* update input windows for streams */
        h2_ihash_iter(m->streams, update_window, m);
        if (on_resume && !h2_iq_empty(m->readyq)) {
            n = h2_iq_mshift(m->readyq, ids, H2_ALEN(ids));
            for (i = 0; i < n; ++i) {
                stream = h2_ihash_get(m->streams, ids[i]);
                if (stream) {
                    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                                  "h2_mplx(%ld-%d): on_resume", 
                                  m->id, stream->id);
                    on_resume(on_ctx, stream);
                }
            }
        }
        
        leave_mutex(m, acquired);
    }
    return status;
}

apr_status_t h2_mplx_keep_active(h2_mplx *m, int stream_id)
{
    apr_status_t status;
    int acquired;
    
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        h2_stream *s = h2_ihash_get(m->streams, stream_id);
        if (s) {
            h2_iq_append(m->readyq, stream_id);
        }
        leave_mutex(m, acquired);
    }
    return status;
}

int h2_mplx_awaits_data(h2_mplx *m)
{
    apr_status_t status;
    int acquired, waiting = 1;
     
    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
        if (h2_ihash_empty(m->streams)) {
            waiting = 0;
        }
        if (h2_iq_empty(m->q) && h2_ihash_empty(m->tasks)) {
            waiting = 0;
        }
        leave_mutex(m, acquired);
    }
    return waiting;
}
