static apr_status_t open_response(h2_task_output *output, ap_filter_t *f,
                                  apr_bucket_brigade *bb, const char *caller)
{
    h2_response *response;
    response = h2_from_h1_get_response(output->from_h1);
    if (!response) {
        if (f) {
            /* This happens currently when ap_die(status, r) is invoked
             * by a read request filter. */
            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, output->task->c, APLOGNO(03204)
                          "h2_task_output(%s): write without response by %s "
                          "for %s %s %s",
                          output->task->id, caller, 
                          output->task->request->method, 
                          output->task->request->authority, 
                          output->task->request->path);
            output->task->c->aborted = 1;
        }
        if (output->task->io) {
            apr_thread_cond_broadcast(output->task->io);
        }
        return APR_ECONNABORTED;
    }
    
    if (h2_task_logio_add_bytes_out) {
        /* count headers as if we'd do a HTTP/1.1 serialization */
        output->written = h2_util_table_bytes(response->headers, 3)+1;
        h2_task_logio_add_bytes_out(output->task->c, output->written);
    }
    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, output->task->c, APLOGNO(03348)
                  "h2_task(%s): open response to %s %s %s",
                  output->task->id, output->task->request->method, 
                  output->task->request->authority, 
                  output->task->request->path);
    return h2_mplx_out_open(output->task->mplx, output->task->stream_id, 
                            response, f, bb, output->task->io);
}