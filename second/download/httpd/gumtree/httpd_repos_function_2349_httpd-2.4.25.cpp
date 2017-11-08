static int purge_stream(void *ctx, void *val) 
{
    h2_mplx *m = ctx;
    h2_stream *stream = val;
    int stream_id = stream->id;
    h2_task *task;

    /* stream_cleanup clears all buffers and destroys any buckets
     * that might hold references into task space. Needs to be done
     * before task destruction, otherwise it will complain. */
    h2_stream_cleanup(stream);
    
    task = h2_ihash_get(m->tasks, stream_id);    
    if (task) {
        task_destroy(m, task, 1);
    }
    
    h2_stream_destroy(stream);
    h2_ihash_remove(m->spurge, stream_id);
    return 0;
}