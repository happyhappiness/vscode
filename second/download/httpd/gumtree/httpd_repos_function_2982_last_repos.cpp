apr_status_t h2_workers_unregister(h2_workers *workers, struct h2_mplx *m)
{
    return h2_fifo_remove(workers->mplxs, m);
}