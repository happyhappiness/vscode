apr_status_t h2_workers_register(h2_workers *workers, struct h2_mplx *m)
{
    apr_status_t status = h2_fifo_push(workers->mplxs, m);
    wake_idle_worker(workers);
    return status;
}