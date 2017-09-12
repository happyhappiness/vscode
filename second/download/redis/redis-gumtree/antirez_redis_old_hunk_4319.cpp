     * file system when Redis exists. */
    unlink("/tmp/redisvm");

    /* Initialize threaded I/O */
    server.io_jobs = listCreate();
    server.io_done = listCreate();
    server.io_clients = listCreate();
    pthread_mutex_init(&server.io_mutex,NULL);
    server.io_active_threads = 0;
}

/* Mark the page as used */
