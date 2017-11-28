int
squidaio_operations_pending(void)
{
    return request_queue_len + (done_requests.head ? 1 : 0);
}