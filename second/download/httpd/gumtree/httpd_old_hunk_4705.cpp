
apr_status_t h2_mplx_dispatch_master_events(h2_mplx *m, 
                                            stream_ev_callback *on_resume, 
                                            void *on_ctx)
{
    h2_stream *stream;
    int n;
    
    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
                  "h2_mplx(%ld): dispatch events", m->id);        
    apr_atomic_set32(&m->event_pending, 0);

    /* update input windows for streams */
    h2_ihash_iter(m->streams, report_consumption_iter, m);    
    purge_streams(m, 1);
    
    n = h2_fifo_count(m->readyq);
    while (n > 0 
           && (h2_fifo_try_pull(m->readyq, (void**)&stream) == APR_SUCCESS)) {
        --n;
        on_resume(on_ctx, stream);
    }
    
    return APR_SUCCESS;
}

apr_status_t h2_mplx_keep_active(h2_mplx *m, h2_stream *stream)
