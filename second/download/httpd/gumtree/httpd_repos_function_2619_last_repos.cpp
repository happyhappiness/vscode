int h2_proxy_iq_remove(h2_proxy_iqueue *q, int sid)
{
    int i;
    for (i = 0; i < q->nelts; ++i) {
        if (sid == q->elts[(q->head + i) % q->nalloc]) {
            break;
        }
    }
    
    if (i < q->nelts) {
        ++i;
        for (; i < q->nelts; ++i) {
            q->elts[(q->head+i-1)%q->nalloc] = q->elts[(q->head+i)%q->nalloc];
        }
        --q->nelts;
        return 1;
    }
    return 0;
}