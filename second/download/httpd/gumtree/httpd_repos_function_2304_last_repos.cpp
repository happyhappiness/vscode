static int iindex_of(h2_ififo *fifo, int id)
{
    int i;
    
    for (i = 0; i < fifo->count; ++i) {
        if (id == fifo->elems[inth_index(fifo, i)]) {
            return i;
        }
    }
    return -1;
}