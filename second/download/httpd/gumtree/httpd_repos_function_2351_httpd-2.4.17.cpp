int h2_task_has_started(h2_task *task)
{
    AP_DEBUG_ASSERT(task);
    return apr_atomic_read32(&task->has_started);
}