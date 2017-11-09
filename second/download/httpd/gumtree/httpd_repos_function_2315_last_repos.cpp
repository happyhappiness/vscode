apr_status_t h2_ififo_try_push(h2_ififo *fifo, int id)
{
    return ififo_push(fifo, id, 0);
}