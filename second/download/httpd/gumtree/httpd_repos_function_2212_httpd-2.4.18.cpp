void h2_tq_add(h2_task_queue *q, int sid, h2_tq_cmp *cmp, void *ctx)
{
    int i;
    
    if (q->nelts >= q->nalloc) {
        tq_grow(q, q->nalloc * 2);
    }
    
    i = (q->head + q->nelts) % q->nalloc;
    q->elts[i] = sid;
    ++q->nelts;
    
    /* bubble it to the front of the queue */
    tq_bubble_up(q, i, q->head, cmp, ctx);
}