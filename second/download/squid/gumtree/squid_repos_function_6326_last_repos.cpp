void
squidaio_shutdown(void)
{
    squidaio_thread_t *threadp;
    int i;
    HANDLE * hthreads;

    if (!squidaio_initialised)
        return;

    /* This is the same as in squidaio_sync */
    do {
        squidaio_poll_queues();
    } while (request_queue_len > 0);

    hthreads = (HANDLE *) xcalloc (NUMTHREADS, sizeof (HANDLE));

    threadp = threads;

    for (i = 0; i < NUMTHREADS; ++i) {
        threadp->exit = 1;
        hthreads[i] = threadp->thread;
        threadp = threadp->next;
    }

    ReleaseMutex(request_queue.mutex);
    ResetEvent(request_queue.cond);
    ReleaseMutex(done_queue.mutex);
    ResetEvent(done_queue.cond);
    Sleep(0);

    WaitForMultipleObjects(NUMTHREADS, hthreads, TRUE, 2000);

    for (i = 0; i < NUMTHREADS; ++i) {
        CloseHandle(hthreads[i]);
    }

    CloseHandle(main_thread);
    CommIO::NotifyIOClose();

    squidaio_initialised = 0;
    xfree(hthreads);
}