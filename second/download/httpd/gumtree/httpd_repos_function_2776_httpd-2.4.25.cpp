h2_worker *h2_worker_create(int id,
                            apr_pool_t *pool,
                            apr_threadattr_t *attr,
                            h2_worker_mplx_next_fn *get_next,
                            h2_worker_done_fn *worker_done,
                            void *ctx)
{
    h2_worker *w = apr_pcalloc(pool, sizeof(h2_worker));
    if (w) {
        w->id = id;
        APR_RING_ELEM_INIT(w, link);
        w->get_next = get_next;
        w->worker_done = worker_done;
        w->ctx = ctx;
        apr_thread_create(&w->thread, attr, execute, w, pool);
    }
    return w;
}