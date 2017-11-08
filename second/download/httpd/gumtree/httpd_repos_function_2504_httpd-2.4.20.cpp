void h2_task_set_io_blocking(h2_task *task, int blocking)
{
    task->blocking = blocking;
}