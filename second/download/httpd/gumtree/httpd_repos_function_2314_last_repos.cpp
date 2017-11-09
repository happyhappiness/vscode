apr_status_t h2_ififo_push(h2_ififo *fifo, int id)
{
    return ififo_push(fifo, id, 1);
}