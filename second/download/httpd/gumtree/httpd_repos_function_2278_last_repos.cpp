static int iq_bubble_down(h2_iqueue *q, int i, int bottom, 
                          h2_iq_cmp *cmp, void *ctx)
{
    int next;
    while (((next = (q->nalloc + i + 1) % q->nalloc), i != bottom) 
           && (*cmp)(q->elts[i], q->elts[next], ctx) > 0) {
        iq_swap(q, next, i);
        i = next;
    }
    return i;
}