int h2_tq_empty(h2_task_queue *q)
{
    return H2_TASK_LIST_EMPTY(&q->tasks);
}