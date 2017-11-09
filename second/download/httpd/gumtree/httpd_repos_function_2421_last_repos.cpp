static void stream_output_consumed(void *ctx, 
                                   h2_bucket_beam *beam, apr_off_t length)
{
    h2_stream *stream = ctx;
    h2_task *task = stream->task;
    
    if (length > 0 && task && task->assigned) {
        h2_req_engine_out_consumed(task->assigned, task->c, length); 
    }
}