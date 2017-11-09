static apr_status_t pull_head(h2_fifo *fifo, void **pelem, int block)
{
    apr_status_t rv;
    
    if ((rv = check_not_empty(fifo, block)) != APR_SUCCESS) {
        *pelem = NULL;
        return rv;
    }
    *pelem = fifo->elems[fifo->head];
    --fifo->count;
    if (fifo->count > 0) {
        fifo->head = nth_index(fifo, 1);
        if (fifo->count+1 == fifo->nelems) {
            apr_thread_cond_broadcast(fifo->not_full);
        }
    }
    return APR_SUCCESS;
}