int h2_proxy_iq_shift(h2_proxy_iqueue *q)
{
    int sid;
    
    if (q->nelts <= 0) {
        return 0;
    }
    
    sid = q->elts[q->head];
    q->head = (q->head + 1) % q->nalloc;
    q->nelts--;
    
    return sid;
}