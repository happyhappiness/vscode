apr_thread_t *h2_worker_get_thread(h2_worker *worker)
{
    return worker->thread;
}