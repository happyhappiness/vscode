static int report_consumption_iter(void *ctx, void *val)
{
    h2_stream *stream = val;
    h2_mplx *m = ctx;
    
    input_consumed_signal(m, stream);
    if (stream->state == H2_SS_CLOSED_L
        && (!stream->task || stream->task->worker_done)) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, 
                      H2_STRM_LOG(APLOGNO(10026), stream, "remote close missing")); 
        nghttp2_submit_rst_stream(stream->session->ngh2, NGHTTP2_FLAG_NONE, 
                                  stream->id, NGHTTP2_NO_ERROR);
    }
    return 1;
}