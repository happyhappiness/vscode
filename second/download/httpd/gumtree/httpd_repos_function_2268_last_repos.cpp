int h2_iq_add(h2_iqueue *q, int sid, h2_iq_cmp *cmp, void *ctx)
{
    int i;
    
    if (h2_iq_contains(q, sid)) {
        return 0;
    }
    if (q->nelts >= q->nalloc) {
        iq_grow(q, q->nalloc * 2);
    }
    i = (q->head + q->nelts) % q->nalloc;
    q->elts[i] = sid;
    ++q->nelts;
    
    if (cmp) {
        /* bubble it to the front of the queue */
        iq_bubble_up(q, i, q->head, cmp, ctx);
    }
    return 1;
}