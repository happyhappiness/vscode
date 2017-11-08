int h2_task_has_finished(h2_task *task)
{
    return apr_atomic_read32(&task->has_finished);
}