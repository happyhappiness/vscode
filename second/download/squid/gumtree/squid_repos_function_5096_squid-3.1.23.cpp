static DWORD WINAPI
squidaio_thread_loop(LPVOID lpParam)
{
    squidaio_thread_t *threadp = (squidaio_thread_t *)lpParam;
    squidaio_request_t *request;
    HANDLE cond; /* local copy of the event queue because win32 event handles
                              * don't atomically release the mutex as cond variables do. */

    /* lock the thread info */

    if (WAIT_FAILED == WaitForSingleObject(request_queue.mutex, INFINITE)) {
        fatal("Can't get ownership of mutex\n");
    }

    /* duplicate the handle */
    if (!DuplicateHandle(GetCurrentProcess(),    /* pseudo handle, don't close */
                         request_queue.cond,     /* handle to copy */
                         GetCurrentProcess(),    /* pseudo handle, don't close */
                         &cond,
                         0,                      /* required access */
                         FALSE,                  /* child process's don't inherit the handle */
                         DUPLICATE_SAME_ACCESS))
        fatal("Can't duplicate mutex handle\n");

    if (!ReleaseMutex(request_queue.mutex)) {
        CloseHandle(cond);
        fatal("Can't release mutex\n");
    }

    Sleep(0);

    while (1) {
        DWORD rv;
        threadp->current_req = request = NULL;
        request = NULL;
        /* Get a request to process */
        threadp->status = _THREAD_WAITING;

        if (threadp->exit) {
            CloseHandle(request_queue.mutex);
            CloseHandle(cond);
            return 0;
        }

        rv = WaitForSingleObject(request_queue.mutex, INFINITE);

        if (rv == WAIT_FAILED) {
            CloseHandle(cond);
            return 1;
        }

        while (!request_queue.head) {
            if (!ReleaseMutex(request_queue.mutex)) {
                CloseHandle(cond);
                threadp->status = _THREAD_FAILED;
                return 1;
            }

            Sleep(0);
            rv = WaitForSingleObject(cond, INFINITE);

            if (rv == WAIT_FAILED) {
                CloseHandle(cond);
                return 1;
            }

            rv = WaitForSingleObject(request_queue.mutex, INFINITE);

            if (rv == WAIT_FAILED) {
                CloseHandle(cond);
                return 1;
            }
        }

        request = request_queue.head;

        if (request)
            request_queue.head = request->next;

        if (!request_queue.head)
            request_queue.tailp = &request_queue.head;

        if (!ReleaseMutex(request_queue.mutex)) {
            CloseHandle(cond);
            return 1;
        }

        Sleep(0);

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
        rv = WaitForSingleObject(done_queue.mutex, INFINITE);

        if (rv == WAIT_FAILED) {
            CloseHandle(cond);
            return 1;
        }

        *done_queue.tailp = request;
        done_queue.tailp = &request->next;

        if (!ReleaseMutex(done_queue.mutex)) {
            CloseHandle(cond);
            return 1;
        }

        CommIO::NotifyIOCompleted();
        Sleep(0);
        threadp->requests++;
    }				/* while forever */

    CloseHandle(cond);

    return 0;
}