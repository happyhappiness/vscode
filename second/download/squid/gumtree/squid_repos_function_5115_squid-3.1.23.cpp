squidaio_result_t *
squidaio_poll_done(void)
{
    squidaio_request_t *request;
    squidaio_result_t *resultp;
    int cancelled;
    int polled = 0;

AIO_REPOLL:
    request = done_requests.head;

    if (request == NULL && !polled) {
        CommIO::ResetNotifications();
        squidaio_poll_queues();
        polled = 1;
        request = done_requests.head;
    }

    if (!request) {
        return NULL;
    }

    debugs(43, 9, "squidaio_poll_done: " << request << " type=" << request->request_type << " result=" << request->resultp);
    done_requests.head = request->next;

    if (!done_requests.head)
        done_requests.tailp = &done_requests.head;

    resultp = request->resultp;

    cancelled = request->cancelled;

    squidaio_debug(request);

    debugs(43, 5, "DONE: " << request->ret << " -> " << request->err);

    squidaio_cleanup_request(request);

    if (cancelled)
        goto AIO_REPOLL;

    return resultp;
}