apr_status_t h2_mplx_process(h2_mplx *m, struct h2_stream *stream, 
                             h2_stream_pri_cmp *cmp, void *ctx)
{
    apr_status_t status;
    
    H2_MPLX_ENTER(m);

    if (m->aborted) {
        status = APR_ECONNABORTED;
    }
    else {
        status = APR_SUCCESS;
        h2_ihash_add(m->streams, stream);
        if (h2_stream_is_ready(stream)) {
            /* already have a response */
            check_data_for(m, stream, 0);
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          H2_STRM_MSG(stream, "process, add to readyq")); 
        }
        else {
            h2_iq_add(m->q, stream->id, cmp, ctx);
            register_if_needed(m);                
            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                          H2_STRM_MSG(stream, "process, added to q")); 
        }
    }

    H2_MPLX_LEAVE(m);
    return status;
}