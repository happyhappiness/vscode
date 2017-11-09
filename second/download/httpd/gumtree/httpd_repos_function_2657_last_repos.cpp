static int nth_index(h2_proxy_fifo *fifo, int n) 
{
    return (fifo->head + n) % fifo->nelems;
}