static void
squidaio_poll_queues(void)
{
    /* kick "overflow" request queue */

    if (request_queue2.head &&
            (WaitForSingleObject(request_queue.mutex, 0 )== WAIT_OBJECT_0)) {
        *request_queue.tailp = request_queue2.head;
        request_queue.tailp = request_queue2.tailp;

        if (!SetEvent(request_queue.cond))
            fatal("couldn't push queue\n");

        if (!ReleaseMutex(request_queue.mutex)) {
            /* unexpected error */
        }

        Sleep(0);
        request_queue2.head = NULL;
        request_queue2.tailp = &request_queue2.head;
    }

    /* poll done queue */
    if (done_queue.head &&
            (WaitForSingleObject(done_queue.mutex, 0)==WAIT_OBJECT_0)) {

        struct squidaio_request_t *requests = done_queue.head;
        done_queue.head = NULL;
        done_queue.tailp = &done_queue.head;

        if (!ReleaseMutex(done_queue.mutex)) {
            /* unexpected error */
        }

        Sleep(0);
        *done_requests.tailp = requests;
        request_queue_len -= 1;

        while (requests->next) {
            requests = requests->next;
            request_queue_len -= 1;
        }

        done_requests.tailp = &requests->next;
    }
}