void h2_task_set_finished(h2_task *task)
{
    apr_atomic_set32(&task->has_finished, 1);
}