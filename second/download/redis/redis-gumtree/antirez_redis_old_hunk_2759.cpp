void *bioProcessBackgroundJobs(void *arg) {
    struct bio_job *job;
    unsigned long type = (unsigned long) arg;

    pthread_detach(pthread_self());
    pthread_mutex_lock(&bio_mutex[type]);
    while(1) {
        listNode *ln;

