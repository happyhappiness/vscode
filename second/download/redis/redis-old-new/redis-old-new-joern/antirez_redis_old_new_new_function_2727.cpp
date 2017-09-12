void *bioProcessBackgroundJobs(void *arg) {
    struct bio_job *job;
    REDIS_NOTUSED(arg);

    pthread_detach(pthread_self());
    pthread_mutex_lock(&bio_mutex);
    while(1) {
        listNode *ln;

        /* The loop always starts with the lock hold. */
        if (listLength(bio_jobs) == 0) {
            pthread_cond_wait(&bio_condvar,&bio_mutex);
            continue;
        }
        /* Pop the job from the queue. */
        ln = listFirst(bio_jobs);
        job = ln->value;
        listDelNode(bio_jobs,ln);
        /* It is now possible to unlock the background system as we know have
         * a stand alone job structure to process.*/
        pthread_mutex_unlock(&bio_mutex);

        /* Process the job accordingly to its type. */
        if (job->type == REDIS_BIO_CLOSE_FILE) {
            printf("Closing file...\n");
            close((long)job->data);
        } else {
            redisPanic("Wrong job type in bioProcessBackgroundJobs().");
        }
        zfree(job);

        /* Lock again before reiterating the loop, if there are no longer
         * jobs to process we'll block again in pthread_cond_wait(). */
        pthread_mutex_lock(&bio_mutex);
    }
}