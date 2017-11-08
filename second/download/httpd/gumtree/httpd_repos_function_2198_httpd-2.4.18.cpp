h2_task_output *h2_task_output_create(h2_task *task, apr_pool_t *pool)
{
    h2_task_output *output = apr_pcalloc(pool, sizeof(h2_task_output));
    
    if (output) {
        output->task = task;
        output->state = H2_TASK_OUT_INIT;
        output->from_h1 = h2_from_h1_create(task->stream_id, pool);
        if (!output->from_h1) {
            return NULL;
        }
    }
    return output;
}