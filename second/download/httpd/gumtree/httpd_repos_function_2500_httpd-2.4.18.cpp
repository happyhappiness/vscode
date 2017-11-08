apr_socket_t *h2_worker_get_socket(h2_worker *worker)
{
    return worker->socket;
}