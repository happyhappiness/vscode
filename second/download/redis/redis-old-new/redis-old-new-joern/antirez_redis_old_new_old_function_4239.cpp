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
        iojob *j;
        listNode *ln;
        robj *key;
        struct dictEntry *de;

        redisLog(REDIS_DEBUG,"Processing I/O completed job");
        assert(listLength(server.io_processed) != 0);

        /* Get the processed element (the oldest one) */
        lockThreadedIO();
        ln = listFirst(server.io_processed);
        j = ln->value;
        listDelNode(server.io_processed,ln);
        unlockThreadedIO();
        /* If this job is marked as canceled, just ignore it */
        if (j->canceled) {
            freeIOJob(j);
            continue;
        }
        /* Post process it in the main thread, as there are things we
         * can do just here to avoid race conditions and/or invasive locks */
        de = dictFind(j->db->dict,j->key);
        assert(de != NULL);
        key = dictGetEntryKey(de);
        if (j->type == REDIS_IOJOB_LOAD) {
            /* Key loaded, bring it at home */
            key->storage = REDIS_VM_MEMORY;
            key->vm.atime = server.unixtime;
            vmMarkPagesFree(key->vm.page,key->vm.usedpages);
            redisLog(REDIS_DEBUG, "VM: object %s loaded from disk (threaded)",
                (unsigned char*) key->ptr);
            server.vm_stats_swapped_objects--;
            server.vm_stats_swapins++;
            freeIOJob(j);
        } else if (j->type == REDIS_IOJOB_PREPARE_SWAP) {
            /* Now we know the amount of pages required to swap this object.
             * Let's find some space for it, and queue this task again
             * rebranded as REDIS_IOJOB_DO_SWAP. */
            if (vmFindContiguousPages(&j->page,j->pages) == REDIS_ERR) {
                /* Ooops... no space! */
                freeIOJob(j);
            } else {
                j->type = REDIS_IOJOB_DO_SWAP;
                lockThreadedIO();
                queueIOJob(j);
                unlockThreadedIO();
            }
        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
            robj *val;

            /* Key swapped. We can finally free some memory. */
            val = dictGetEntryVal(de);
            key->vm.page = j->page;
            key->vm.usedpages = j->pages;
            key->storage = REDIS_VM_SWAPPED;
            key->vtype = j->val->type;
            decrRefCount(val); /* Deallocate the object from memory. */
            vmMarkPagesUsed(j->page,j->pages);
            redisLog(REDIS_DEBUG,
                "VM: object %s swapped out at %lld (%lld pages) (threaded)",
                (unsigned char*) key->ptr,
                (unsigned long long) j->page, (unsigned long long) j->pages);
            server.vm_stats_swapped_objects++;
            server.vm_stats_swapouts++;
            freeIOJob(j);
        }
    }
    if (retval < 0 && errno != EAGAIN) {
        redisLog(REDIS_WARNING,
            "WARNING: read(2) error in vmThreadedIOCompletedJob() %s",
            strerror(errno));
    }
}