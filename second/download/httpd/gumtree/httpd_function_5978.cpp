static int task_print(void *ctx, void *val)
{
    h2_mplx *m = ctx;
    h2_task *task = val;

    if (task && task->request) {
        h2_stream *stream = h2_ihash_get(m->streams, task->stream_id);

        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%s): %s %s %s -> %s %d"
                      "[orph=%d/started=%d/done=%d]", 
                      task->id, task->request->method, 
                      task->request->authority, task->request->path,
                      task->response? "http" : (task->rst_error? "reset" : "?"),
                      task->response? task->response->http_status : task->rst_error,
                      (stream? 0 : 1), task->worker_started, 
                      task->worker_done);
    }
    else if (task) {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-%d): NULL", m->id, task->stream_id);
    }
    else {
        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
                      "->03198: h2_stream(%ld-NULL): NULL", m->id);
    }
    return 1;
}