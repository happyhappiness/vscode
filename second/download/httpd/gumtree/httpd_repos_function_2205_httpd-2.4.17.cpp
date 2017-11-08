void h2_tq_append(h2_task_queue *q, struct h2_task *task)
{
    H2_TASK_LIST_INSERT_TAIL(&q->tasks, task);
}