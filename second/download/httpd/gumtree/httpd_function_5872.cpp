static apr_status_t open_response(h2_task *task)
{
    h2_response *response;
    response = h2_from_h1_get_response(task->output.from_h1);
    if (!response) {
        /* This happens currently when ap_die(status, r) is invoked
         * by a read request filter. */
        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03204)
                      "h2_task(%s): write without response for %s %s %s",
                      task->id, 
                      task->request->method, 
                      task->request->authority, 
                      task->request->path);
        task->c->aborted = 1;
        return APR_ECONNABORTED;
    }
    
    if (h2_task_logio_add_bytes_out) {
        /* count headers as if we'd do a HTTP/1.1 serialization */
        task->output.written = h2_util_table_bytes(response->headers, 3)+1;
        h2_task_logio_add_bytes_out(task->c, task->output.written);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, APLOGNO(03348)
                  "h2_task(%s): open response to %s %s %s",
                  task->id, task->request->method, 
                  task->request->authority, 
                  task->request->path);
    return h2_mplx_out_open(task->mplx, task->stream_id, response);
}