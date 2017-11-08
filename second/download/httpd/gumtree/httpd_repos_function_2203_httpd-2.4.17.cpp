static int in_list(h2_task_queue *q, h2_task *task)
{
    h2_task *e;
    for (e = H2_TASK_LIST_FIRST(&q->tasks); 
         e != H2_TASK_LIST_SENTINEL(&q->tasks);
         e = H2_TASK_NEXT(e)) {
        if (e == task) {
            return 1;
        }
    }
    return 0;
}