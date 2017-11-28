void
squidaio_init(void)
{
    int i;
    squidaio_thread_t *threadp;

    if (squidaio_initialised)
        return;

    if (!DuplicateHandle(GetCurrentProcess(), /* pseudo handle, don't close */
                         GetCurrentThread(),  /* pseudo handle to copy */
                         GetCurrentProcess(), /* pseudo handle, don't close */
                         &main_thread,
                         0,                   /* required access */
                         FALSE,               /* child process's don't inherit the handle */
                         DUPLICATE_SAME_ACCESS)) {
        /* spit errors */
        fatal("Couldn't get current thread handle");
    }

    /* Initialize request queue */
    if ((request_queue.mutex = CreateMutex(NULL,    /* no inheritance */
                                           FALSE,   /* start unowned (as per mutex_init) */
                                           NULL)    /* no name */
        ) == NULL) {
        fatal("Failed to create mutex");
    }

    if ((request_queue.cond = CreateEvent(NULL,     /* no inheritance */
                                          FALSE,    /* auto signal reset - which I think is pthreads like ? */
                                          FALSE,    /* start non signaled */
                                          NULL)     /* no name */
        ) == NULL) {
        fatal("Failed to create condition variable");
    }

    request_queue.head = NULL;

    request_queue.tailp = &request_queue.head;

    request_queue.requests = 0;

    request_queue.blocked = 0;

    /* Initialize done queue */

    if ((done_queue.mutex = CreateMutex(NULL,  /* no inheritance */
                                        FALSE, /* start unowned (as per mutex_init) */
                                        NULL)  /* no name */
        ) == NULL) {
        fatal("Failed to create mutex");
    }

    if ((done_queue.cond = CreateEvent(NULL,  /* no inheritance */
                                       TRUE,  /* manually signaled - which I think is pthreads like ? */
                                       FALSE, /* start non signaled */
                                       NULL)  /* no name */
        ) == NULL) {
        fatal("Failed to create condition variable");
    }

    done_queue.head = NULL;

    done_queue.tailp = &done_queue.head;

    done_queue.requests = 0;

    done_queue.blocked = 0;

    // Initialize the thread I/O pipes before creating any threads
    // see bug 3189 comment 5 about race conditions.
    CommIO::Initialize();

    /* Create threads and get them to sit in their wait loop */
    squidaio_thread_pool = memPoolCreate("aio_thread", sizeof(squidaio_thread_t));

    assert(NUMTHREADS);

    for (i = 0; i < NUMTHREADS; ++i) {
        threadp = (squidaio_thread_t *)squidaio_thread_pool->alloc();
        threadp->status = _THREAD_STARTING;
        threadp->current_req = NULL;
        threadp->requests = 0;
        threadp->next = threads;
        threads = threadp;

        if ((threadp->thread = CreateThread(NULL,                   /* no security attributes */
                                            0,                      /* use default stack size */
                                            squidaio_thread_loop,   /* thread function */
                                            threadp,                /* argument to thread function */
                                            0,                      /* use default creation flags */
                                            &(threadp->dwThreadId)) /* returns the thread identifier */
            ) == NULL) {
            fprintf(stderr, "Thread creation failed\n");
            threadp->status = _THREAD_FAILED;
            continue;
        }

        /* Set the new thread priority above parent process */
        SetThreadPriority(threadp->thread,THREAD_PRIORITY_ABOVE_NORMAL);
    }

    /* Create request pool */
    squidaio_request_pool = memPoolCreate("aio_request", sizeof(squidaio_request_t));

    squidaio_large_bufs = memPoolCreate("squidaio_large_bufs", AIO_LARGE_BUFS);

    squidaio_medium_bufs = memPoolCreate("squidaio_medium_bufs", AIO_MEDIUM_BUFS);

    squidaio_small_bufs = memPoolCreate("squidaio_small_bufs", AIO_SMALL_BUFS);

    squidaio_tiny_bufs = memPoolCreate("squidaio_tiny_bufs", AIO_TINY_BUFS);

    squidaio_micro_bufs = memPoolCreate("squidaio_micro_bufs", AIO_MICRO_BUFS);

    squidaio_initialised = 1;
}