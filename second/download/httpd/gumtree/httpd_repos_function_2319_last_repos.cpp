apr_status_t h2_ififo_try_pull(h2_ififo *fifo, int *pi)
{
    return ififo_pull(fifo, pi, 0);
}