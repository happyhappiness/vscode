static void spawnIOThread(void) {
    pthread_t thread;
    sigset_t mask, omask;

    sigemptyset(&mask);
    sigaddset(&mask,SIGCHLD);
    sigaddset(&mask,SIGHUP);
    sigaddset(&mask,SIGPIPE);
    pthread_sigmask(SIG_SETMASK, &mask, &omask);
    pthread_create(&thread,&server.io_threads_attr,IOThreadEntryPoint,NULL);
    pthread_sigmask(SIG_SETMASK, &omask, NULL);
    server.io_active_threads++;
}