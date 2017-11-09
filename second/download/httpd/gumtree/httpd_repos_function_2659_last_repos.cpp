static int index_of(h2_proxy_fifo *fifo, void *elem)
{
    int i;
    
    for (i = 0; i < fifo->count; ++i) {
        if (elem == fifo->elems[nth_index(fifo, i)]) {
            return i;
        }
    }
    return -1;
}