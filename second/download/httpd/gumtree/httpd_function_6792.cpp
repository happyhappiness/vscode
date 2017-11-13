static int report_stream_iter(void *ctx, void *val) {
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    h2_task *task = stream->task;
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
                  H2_STRM_MSG(stream, "started=%d, scheduled=%d, ready=%d, "
                              "out_buffer=%ld"), 
                  !!stream->task, stream->scheduled, h2_stream_is_ready(stream),
                  (long)h2_beam_get_buffered(stream->output));
    if (task) {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      H2_STRM_MSG(stream, "->03198: %s %s %s"
                      "[started=%d/done=%d/frozen=%d]"), 
                      task->request->method, task->request->authority, 
                      task->request->path, task->worker_started, 
                      task->worker_done, task->frozen);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, /* NO APLOGNO */
                      H2_STRM_MSG(stream, "->03198: no task"));
    }
    return 1;
}