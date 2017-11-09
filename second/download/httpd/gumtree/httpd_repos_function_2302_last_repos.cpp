static int inth_index(h2_ififo *fifo, int n) 
{
    return (fifo->head + n) % fifo->nelems;
}