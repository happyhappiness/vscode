static void spawnIOThread(void) {
    pthread_t thread;
    sigset_t mask, omask;
    int err;

    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);
    sigaddset(&mask,SIGHUP);
    sigaddset(&mask,SIGPIPE);
    pthread_sigmask(SIG_SETMASK, &mask, &omask);
    while ((err = pthread_create(&thread,&server.io_threads_attr,IOThreadEntryPoint,NULL)) != 0) {
        redisLog(REDIS_WARNING,"Unable to spawn an I/O thread: %s",
            strerror(err));
        usleep(1000000);
    }
    pthread_sigmask(SIG_SETMASK, &omask, NULL);
    server.io_active_threads++;
}