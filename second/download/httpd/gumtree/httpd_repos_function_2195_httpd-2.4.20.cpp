h2_task_output *h2_task_output_create(h2_task *task, conn_rec *c)
{
    h2_task_output *output = apr_pcalloc(task->pool, sizeof(h2_task_output));
    if (output) {
        output->task = task;
        output->from_h1 = h2_from_h1_create(task->stream_id, task->pool);
    }
    return output;
}