int h2_worker_is_aborted(h2_worker *worker)
{
    return worker->aborted;
}