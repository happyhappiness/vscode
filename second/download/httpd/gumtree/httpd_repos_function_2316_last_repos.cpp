static apr_status_t ipull_head(h2_ififo *fifo, int *pi, int block)
{
    apr_status_t rv;
    
    if ((rv = icheck_not_empty(fifo, block)) != APR_SUCCESS) {
        *pi = 0;
        return rv;
    }
    *pi = fifo->elems[fifo->head];
    --fifo->count;
    if (fifo->count > 0) {
        fifo->head = inth_index(fifo, 1);
        if (fifo->count+1 == fifo->nelems) {
            apr_thread_cond_broadcast(fifo->not_full);
        }
    }
    return APR_SUCCESS;
}