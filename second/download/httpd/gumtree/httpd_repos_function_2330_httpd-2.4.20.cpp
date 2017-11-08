void h2_iq_add(h2_int_queue *q, int sid, h2_iq_cmp *cmp, void *ctx)
{
    int i;
    
    if (q->nelts >= q->nalloc) {
        tq_grow(q, q->nalloc * 2);
    }
    
    i = (q->head + q->nelts) % q->nalloc;
    q->elts[i] = sid;
    ++q->nelts;
    
    if (cmp) {
        /* bubble it to the front of the queue */
        tq_bubble_up(q, i, q->head, cmp, ctx);
    }
}