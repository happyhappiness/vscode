void
squidaio_shutdown(void)
{
    if (!squidaio_initialised)
        return;

    /* This is the same as in squidaio_sync */
    do {
        squidaio_poll_queues();
    } while (request_queue_len > 0);

    CommIO::NotifyIOClose();

    squidaio_initialised = 0;
}