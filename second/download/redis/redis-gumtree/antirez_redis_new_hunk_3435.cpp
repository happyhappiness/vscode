
/* =================== Virtual Memory - Blocking Side  ====================== */

void dsInit(void) {
    off_t totsize;
    int pipefds[2];
    size_t stacksize;
    struct flock fl;

    zmalloc_enable_thread_safeness(); /* we need thread safe zmalloc() */

    redisLog(REDIS_NOTICE,"Initializing Disk Store at %s", server.ds_path);
    /* Open Disk Store */
    if (dsOpen() != REDIS_OK) {
        redisLog(REDIS_WARNING,"Fatal error opening disk store. Exiting.");
        exit(1);
    };

    /* Initialize threaded I/O for Object Cache */
    server.io_newjobs = listCreate();
    server.io_processing = listCreate();
    server.io_processed = listCreate();
    server.io_ready_clients = listCreate();
    pthread_mutex_init(&server.io_mutex,NULL);
    server.io_active_threads = 0;
    if (pipe(pipefds) == -1) {
        redisLog(REDIS_WARNING,"Unable to intialized DS: pipe(2): %s. Exiting."
            ,strerror(errno));
        exit(1);
    }
