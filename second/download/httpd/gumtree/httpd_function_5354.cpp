static apr_status_t open_if_needed(h2_task_output *output, ap_filter_t *f,
                                   apr_bucket_brigade *bb)
{
    if (output->state == H2_TASK_OUT_INIT) {
        h2_response *response;
        output->state = H2_TASK_OUT_STARTED;
        response = h2_from_h1_get_response(output->from_h1);
        if (!response) {
            if (f) {
                /* This happens currently when ap_die(status, r) is invoked
                 * by a read request filter.
                 */
                ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, f->c,
                              "h2_task_output(%s): write without response "
                              "for %s %s %s",
                              output->env->id, output->env->method, 
                              output->env->authority, output->env->path);
                f->c->aborted = 1;
            }
            if (output->env->io) {
                apr_thread_cond_broadcast(output->env->io);
            }
            return APR_ECONNABORTED;
        }
        
        return h2_mplx_out_open(output->env->mplx, output->env->stream_id, 
                                response, f, bb, output->env->io);
    }
    return APR_EOF;
}