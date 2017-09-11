    return val;
}

#if 0 /* We don't use the following code for now, and bioWaitPendingJobsLE
         probably needs a rewrite using conditional variables instead of the
         current implementation. */
         

/* Wait until the number of pending jobs of the specified type are
 * less or equal to the specified number.
 *
 * This function may block for long time, it should only be used to perform
 * the following tasks:
 *
 * 1) To avoid that the main thread is pushing jobs of a given time so fast
 *    that the background thread can't process them at the same speed.
 *    So before creating a new job of a given type the main thread should
 *    call something like: bioWaitPendingJobsLE(job_type,10000);
 * 2) In order to perform special operations that make it necessary to be sure
 *    no one is touching shared resourced in the background.
 */
void bioWaitPendingJobsLE(int type, unsigned long long num) {
    unsigned long long iteration = 0;

    /* We poll the jobs queue aggressively to start, and gradually relax
     * the polling speed if it is going to take too much time. */
    while(1) {
        iteration++;
        if (iteration > 1000 && iteration <= 10000) {
            usleep(100);
        } else if (iteration > 10000) {
            usleep(1000);
        }
        if (bioPendingJobsOfType(type) <= num) break;
    }
}

/* Return the older job of the specified type. */
time_t bioOlderJobOfType(int type) {
    time_t time;
    listNode *ln;
    struct bio_job *job;

    pthread_mutex_lock(&bio_mutex[type]);
    ln = listFirst(bio_jobs[type]);
    if (ln == NULL) {
        pthread_mutex_unlock(&bio_mutex[type]);
        return 0;
    }
    job = ln->value;
    time = job->time;
    pthread_mutex_unlock(&bio_mutex[type]);
    return time;
}

#endif
