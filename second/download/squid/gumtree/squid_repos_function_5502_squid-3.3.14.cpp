void *
squidaio_thread_loop(void *ptr)
{
    squidaio_thread_t *threadp = (squidaio_thread_t *)ptr;
    squidaio_request_t *request;
    sigset_t newSig;

    /*
     * Make sure to ignore signals which may possibly get sent to
     * the parent squid thread.  Causes havoc with mutex's and
     * condition waits otherwise
     */

    sigemptyset(&newSig);
    sigaddset(&newSig, SIGPIPE);
    sigaddset(&newSig, SIGCHLD);
#if defined(_SQUID_LINUX_THREADS_)

    sigaddset(&newSig, SIGQUIT);
    sigaddset(&newSig, SIGTRAP);
#else

    sigaddset(&newSig, SIGUSR1);
    sigaddset(&newSig, SIGUSR2);
#endif

    sigaddset(&newSig, SIGHUP);
    sigaddset(&newSig, SIGTERM);
    sigaddset(&newSig, SIGINT);
    sigaddset(&newSig, SIGALRM);
    pthread_sigmask(SIG_BLOCK, &newSig, NULL);

    while (1) {
        threadp->current_req = request = NULL;
        request = NULL;
        /* Get a request to process */
        threadp->status = _THREAD_WAITING;
        pthread_mutex_lock(&request_queue.mutex);

        while (!request_queue.head) {
            pthread_cond_wait(&request_queue.cond, &request_queue.mutex);
        }

        request = request_queue.head;

        if (request)
            request_queue.head = request->next;

        if (!request_queue.head)
            request_queue.tailp = &request_queue.head;

        pthread_mutex_unlock(&request_queue.mutex);

        /* process the request */
        threadp->status = _THREAD_BUSY;

        request->next = NULL;

        threadp->current_req = request;

        errno = 0;

        if (!request->cancelled) {
            switch (request->request_type) {

            case _AIO_OP_OPEN:
                squidaio_do_open(request);
                break;

            case _AIO_OP_READ:
                squidaio_do_read(request);
                break;

            case _AIO_OP_WRITE:
                squidaio_do_write(request);
                break;

            case _AIO_OP_CLOSE:
                squidaio_do_close(request);
                break;

            case _AIO_OP_UNLINK:
                squidaio_do_unlink(request);
                break;

#if AIO_OPENDIR			/* Opendir not implemented yet */

            case _AIO_OP_OPENDIR:
                squidaio_do_opendir(request);
                break;
#endif

            case _AIO_OP_STAT:
                squidaio_do_stat(request);
                break;

            default:
                request->ret = -1;
                request->err = EINVAL;
                break;
            }
        } else {		/* cancelled */
            request->ret = -1;
            request->err = EINTR;
        }

        threadp->status = _THREAD_DONE;
        /* put the request in the done queue */
        pthread_mutex_lock(&done_queue.mutex);
        *done_queue.tailp = request;
        done_queue.tailp = &request->next;
        pthread_mutex_unlock(&done_queue.mutex);
        CommIO::NotifyIOCompleted();
        ++ threadp->requests;
    }				/* while forever */

    return NULL;
}