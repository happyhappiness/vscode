void h2_worker_abort(h2_worker *worker)
{
    worker->aborted = 1;
}