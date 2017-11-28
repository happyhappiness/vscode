int
squidaio_sync(void)
{
    /* XXX This might take a while if the queue is large.. */

    do {
        squidaio_poll_queues();
    } while (request_queue_len > 0);

    return squidaio_operations_pending();
}