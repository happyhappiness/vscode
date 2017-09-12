    return 1;
}

/* =================== Virtual Memory - Threaded I/O  ======================= */

/* Every time a thread finished a Job, it writes a byte into the write side
 * of an unix pipe in order to "awake" the main thread, and this function
 * is called. */
static void vmThreadedIOCompletedJob(aeEventLoop *el, int fd, void *privdata,
            int mask)
{
    char buf[1];
    int retval;
    REDIS_NOTUSED(el);
    REDIS_NOTUSED(mask);
    REDIS_NOTUSED(privdata);

    /* For every byte we read in the read side of the pipe, there is one
     * I/O job completed to process. */
    while((retval = read(fd,buf,1)) == 1) {
        redisLog(REDIS_DEBUG,"Processing I/O completed job");
    }
    if (retval < 0 && errno != EAGAIN) {
        redisLog(REDIS_WARNING,
            "WARNING: read(2) error in vmThreadedIOCompletedJob() %s",
            strerror(errno));
    }
}

static void lockThreadedIO(void) {
    pthread_mutex_lock(&server.io_mutex);
}

static void unlockThreadedIO(void) {
    pthread_mutex_unlock(&server.io_mutex);
}

/* Remove the specified object from the threaded I/O queue if still not
 * processed, otherwise make sure to flag it as canceled. */
static void vmCancelThreadedIOJob(robj *o) {
    list *lists[3] = {
        server.io_newjobs, server.io_processing, server.io_processed
    };
    int i;

    assert(o->storage == REDIS_VM_LOADING || o->storage == REDIS_VM_SWAPPING);
    lockThreadedIO();
    /* Search for a matching key in one of the queues */
    for (i = 0; i < 3; i++) {
        listNode *ln;

        listRewind(lists[i]);
        while ((ln = listYield(lists[i])) != NULL) {
            iojob *job = ln->value;

            if (compareStringObjects(job->key,o) == 0) {
                switch(i) {
                case 0: /* io_newjobs */
                    /* If the job was not yet processed the best thing to do
                     * is to remove it from the queue at all */
                    decrRefCount(job->key);
                    if (job->type == REDIS_IOJOB_SWAP)
                        decrRefCount(job->val);
                    listDelNode(lists[i],ln);
                    break;
                case 1: /* io_processing */
                case 2: /* io_processed */
                    job->canceled = 1;
                    break;
                }
                if (o->storage == REDIS_VM_LOADING)
                    o->storage = REDIS_VM_SWAPPED;
                else if (o->storage == REDIS_VM_SWAPPING)
                    o->storage = REDIS_VM_MEMORY;
                unlockThreadedIO();
                return;
            }
        }
    }
    unlockThreadedIO();
    assert(1 != 1); /* We should never reach this */
}

/* ================================= Debugging ============================== */

static void debugCommand(redisClient *c) {
