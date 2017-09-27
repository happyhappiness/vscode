
    apr_threadattr_create(&thread_attr, pchild);
    /* 0 means PTHREAD_CREATE_JOINABLE */
    apr_threadattr_detach_set(thread_attr, 0);

    if (ap_thread_stacksize != 0) {
        apr_threadattr_stacksize_set(thread_attr, ap_thread_stacksize);
    }

    ts->threads = threads;
    ts->listener = NULL;
    ts->child_num_arg = child_num_arg;
    ts->threadattr = thread_attr;
