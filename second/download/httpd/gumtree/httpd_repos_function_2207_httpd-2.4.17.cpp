h2_task *h2_tq_pop_first(h2_task_queue *q)
{
    if (!H2_TASK_LIST_EMPTY(&q->tasks)) {
        h2_task *task = H2_TASK_LIST_FIRST(&q->tasks);
        H2_TASK_REMOVE(task);
        return task;
    }
    return NULL;
}