void h2_task_set_started(h2_task *task)
{
    AP_DEBUG_ASSERT(task);
    apr_atomic_set32(&task->has_started, 1);
}