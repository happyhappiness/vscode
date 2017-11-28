static void
squidaio_queue_request(squidaio_request_t * request)
{
    static int high_start = 0;
    debugs(43, 9, "squidaio_queue_request: " << request << " type=" << request->request_type << " result=" << request->resultp);
    /* Mark it as not executed (failing result, no error) */
    request->ret = -1;
    request->err = 0;
    /* Internal housekeeping */
    request_queue_len += 1;
    request->resultp->_data = request;
    /* Play some tricks with the request_queue2 queue */
    request->next = NULL;

    if (WaitForSingleObject(request_queue.mutex, 0) == WAIT_OBJECT_0) {
        if (request_queue2.head) {
            /* Grab blocked requests */
            *request_queue.tailp = request_queue2.head;
            request_queue.tailp = request_queue2.tailp;
        }

        /* Enqueue request */
        *request_queue.tailp = request;

        request_queue.tailp = &request->next;

        if (!SetEvent(request_queue.cond))
            fatal("Couldn't push queue");

        if (!ReleaseMutex(request_queue.mutex)) {
            /* unexpected error */
            fatal("Couldn't push queue");
        }

        Sleep(0);

        if (request_queue2.head) {
            /* Clear queue of blocked requests */
            request_queue2.head = NULL;
            request_queue2.tailp = &request_queue2.head;
        }
    } else {
        /* Oops, the request queue is blocked, use request_queue2 */
        *request_queue2.tailp = request;
        request_queue2.tailp = &request->next;
    }

    if (request_queue2.head) {
        static int filter = 0;
        static int filter_limit = 8;

        if (++filter >= filter_limit) {
            filter_limit += filter;
            filter = 0;
            debugs(43, DBG_IMPORTANT, "squidaio_queue_request: WARNING - Queue congestion");
        }
    }

    /* Warn if out of threads */
    if (request_queue_len > MAGIC1) {
        static int last_warn = 0;
        static int queue_high, queue_low;

        if (high_start == 0) {
            high_start = (int)squid_curtime;
            queue_high = request_queue_len;
            queue_low = request_queue_len;
        }

        if (request_queue_len > queue_high)
            queue_high = request_queue_len;

        if (request_queue_len < queue_low)
            queue_low = request_queue_len;

        if (squid_curtime >= (last_warn + 15) &&
                squid_curtime >= (high_start + 5)) {
            debugs(43, DBG_IMPORTANT, "squidaio_queue_request: WARNING - Disk I/O overloading");

            if (squid_curtime >= (high_start + 15))
                debugs(43, DBG_IMPORTANT, "squidaio_queue_request: Queue Length: current=" <<
                       request_queue_len << ", high=" << queue_high <<
                       ", low=" << queue_low << ", duration=" <<
                       (long int) (squid_curtime - high_start));

            last_warn = (int)squid_curtime;
        }
    } else {
        high_start = 0;
    }

    /* Warn if seriously overloaded */
    if (request_queue_len > RIDICULOUS_LENGTH) {
        debugs(43, DBG_CRITICAL, "squidaio_queue_request: Async request queue growing uncontrollably!");
        debugs(43, DBG_CRITICAL, "squidaio_queue_request: Syncing pending I/O operations.. (blocking)");
        squidaio_sync();
        debugs(43, DBG_CRITICAL, "squidaio_queue_request: Synced");
    }
}