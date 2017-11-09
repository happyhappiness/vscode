static void *pull_head(h2_proxy_fifo *fifo)
{
    void *elem;
    
    ap_assert(fifo->count > 0);
    elem = fifo->elems[fifo->head];
    --fifo->count;
    if (fifo->count > 0) {
        fifo->head = nth_index(fifo, 1);
        if (fifo->count+1 == fifo->nelems) {
            apr_thread_cond_broadcast(fifo->not_full);
        }
    }
    return elem;
}