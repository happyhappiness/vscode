void h2_tq_destroy(h2_task_queue *q)
{
    while (!H2_TASK_LIST_EMPTY(&q->tasks)) {
        h2_task *task = H2_TASK_LIST_FIRST(&q->tasks);
        H2_TASK_REMOVE(task);
    }
}