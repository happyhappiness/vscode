void
squidaio_init(void)
{
    int i;
    squidaio_thread_t *threadp;

    if (squidaio_initialised)
        return;

    pthread_attr_init(&globattr);

#if HAVE_PTHREAD_ATTR_SETSCOPE

    pthread_attr_setscope(&globattr, PTHREAD_SCOPE_SYSTEM);

#endif
#if HAVE_SCHED_H

    globsched.sched_priority = 1;

#endif

    main_thread = pthread_self();

#if HAVE_SCHED_H && HAVE_PTHREAD_SETSCHEDPARAM

    pthread_setschedparam(main_thread, SCHED_OTHER, &globsched);

#endif
#if HAVE_SCHED_H

    globsched.sched_priority = 2;

#endif
#if HAVE_SCHED_H && HAVE_PTHREAD_ATTR_SETSCHEDPARAM

    pthread_attr_setschedparam(&globattr, &globsched);

#endif

    /* Give each thread a smaller 256KB stack, should be more than sufficient */
    pthread_attr_setstacksize(&globattr, 256 * 1024);

    /* Initialize request queue */
    if (pthread_mutex_init(&(request_queue.mutex), NULL))
        fatal("Failed to create mutex");

    if (pthread_cond_init(&(request_queue.cond), NULL))
        fatal("Failed to create condition variable");

    request_queue.head = NULL;

    request_queue.tailp = &request_queue.head;

    request_queue.requests = 0;

    request_queue.blocked = 0;

    /* Initialize done queue */
    if (pthread_mutex_init(&(done_queue.mutex), NULL))
        fatal("Failed to create mutex");

    if (pthread_cond_init(&(done_queue.cond), NULL))
        fatal("Failed to create condition variable");

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

        if (pthread_create(&threadp->thread, &globattr, squidaio_thread_loop, threadp)) {
            fprintf(stderr, "Thread creation failed\n");
            threadp->status = _THREAD_FAILED;
            continue;
        }
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