static void *IOThreadEntryPoint(void *arg) {
    iojob *j;
    listNode *ln;
    REDIS_NOTUSED(arg);

    pthread_detach(pthread_self());
    while(1) {
        /* Get a new job to process */
        lockThreadedIO();
        if (listLength(server.io_newjobs) == 0) {
            /* No new jobs in queue, exit. */
            printf("Thread %lld exiting, nothing to do\n",
                (long long) pthread_self());
            server.io_active_threads--;
            unlockThreadedIO();
            return NULL;
        }
        ln = listFirst(server.io_newjobs);
        j = ln->value;
        listDelNode(server.io_newjobs,ln);
        /* Add the job in the processing queue */
        j->thread = pthread_self();
        listAddNodeTail(server.io_processing,j);
        ln = listLast(server.io_processing); /* We use ln later to remove it */
        unlockThreadedIO();
        printf("Thread %lld got a new job: %p about key '%s'\n",
            (long long) pthread_self(), (void*)j, (char*)j->key->ptr);

        /* Process the Job */
        if (j->type == REDIS_IOJOB_LOAD) {
        } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
            FILE *fp = fopen("/dev/null","w+");
            j->pages = rdbSavedObjectPages(j->val,fp);
            fclose(fp);
        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
        }

        /* Done: insert the job into the processed queue */
        printf("Thread %lld completed the job: %p\n",
            (long long) pthread_self(), (void*)j);
        lockThreadedIO();
        listDelNode(server.io_processing,ln);
        listAddNodeTail(server.io_processed,j);
        unlockThreadedIO();
        
        /* Signal the main thread there is new stuff to process */
        assert(write(server.io_ready_pipe_write,"x",1) == 1);
    }
    return NULL; /* never reached */
}