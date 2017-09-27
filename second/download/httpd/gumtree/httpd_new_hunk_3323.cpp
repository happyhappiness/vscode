
    /* Setup worker threads */

    /* clear the storage; we may not create all our threads immediately,
     * and we want a 0 entry to indicate a thread which was not created
     */
    threads = ap_calloc(threads_per_child, sizeof(apr_thread_t *));
    ts = apr_palloc(pchild, sizeof(*ts));

    apr_threadattr_create(&thread_attr, pchild);
    /* 0 means PTHREAD_CREATE_JOINABLE */
    apr_threadattr_detach_set(thread_attr, 0);

    if (ap_thread_stacksize != 0) {
