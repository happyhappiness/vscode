void h2_task_destroy(h2_task *task)
{
    if (task->output.beam) {
        h2_beam_log(task->output.beam, task->c, APLOG_TRACE2, "task_destroy");
        h2_beam_destroy(task->output.beam);
        task->output.beam = NULL;
    }
    
    if (task->eor) {
        apr_bucket_destroy(task->eor);
    }
    if (task->pool) {
        apr_pool_destroy(task->pool);
    }
}