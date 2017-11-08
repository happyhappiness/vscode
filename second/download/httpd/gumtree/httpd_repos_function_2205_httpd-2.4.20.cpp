int h2_tq_empty(h2_task_queue *q)
{
    return q->nelts == 0;
}