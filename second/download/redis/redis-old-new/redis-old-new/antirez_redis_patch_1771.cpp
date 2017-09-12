@@ -109,17 +109,6 @@
 
 /* =================== Virtual Memory - Blocking Side  ====================== */
 
-/* Create a VM pointer object. This kind of objects are used in place of
- * values in the key -> value hash table, for swapped out objects. */
-vmpointer *createVmPointer(int vtype) {
-    vmpointer *vp = zmalloc(sizeof(vmpointer));
-
-    vp->type = REDIS_VMPOINTER;
-    vp->storage = REDIS_VM_SWAPPED;
-    vp->vtype = vtype;
-    return vp;
-}
-
 void vmInit(void) {
     off_t totsize;
     int pipefds[2];
@@ -203,124 +192,6 @@ void vmInit(void) {
         oom("creating file event");
 }
 
-/* Mark the page as used */
-void vmMarkPageUsed(off_t page) {
-    off_t byte = page/8;
-    int bit = page&7;
-    redisAssert(vmFreePage(page) == 1);
-    server.vm_bitmap[byte] |= 1<<bit;
-}
-
-/* Mark N contiguous pages as used, with 'page' being the first. */
-void vmMarkPagesUsed(off_t page, off_t count) {
-    off_t j;
-
-    for (j = 0; j < count; j++)
-        vmMarkPageUsed(page+j);
-    server.vm_stats_used_pages += count;
-    redisLog(REDIS_DEBUG,"Mark USED pages: %lld pages at %lld\n",
-        (long long)count, (long long)page);
-}
-
-/* Mark the page as free */
-void vmMarkPageFree(off_t page) {
-    off_t byte = page/8;
-    int bit = page&7;
-    redisAssert(vmFreePage(page) == 0);
-    server.vm_bitmap[byte] &= ~(1<<bit);
-}
-
-/* Mark N contiguous pages as free, with 'page' being the first. */
-void vmMarkPagesFree(off_t page, off_t count) {
-    off_t j;
-
-    for (j = 0; j < count; j++)
-        vmMarkPageFree(page+j);
-    server.vm_stats_used_pages -= count;
-    redisLog(REDIS_DEBUG,"Mark FREE pages: %lld pages at %lld\n",
-        (long long)count, (long long)page);
-}
-
-/* Test if the page is free */
-int vmFreePage(off_t page) {
-    off_t byte = page/8;
-    int bit = page&7;
-    return (server.vm_bitmap[byte] & (1<<bit)) == 0;
-}
-
-/* Find N contiguous free pages storing the first page of the cluster in *first.
- * Returns REDIS_OK if it was able to find N contiguous pages, otherwise
- * REDIS_ERR is returned.
- *
- * This function uses a simple algorithm: we try to allocate
- * REDIS_VM_MAX_NEAR_PAGES sequentially, when we reach this limit we start
- * again from the start of the swap file searching for free spaces.
- *
- * If it looks pretty clear that there are no free pages near our offset
- * we try to find less populated places doing a forward jump of
- * REDIS_VM_MAX_RANDOM_JUMP, then we start scanning again a few pages
- * without hurry, and then we jump again and so forth...
- *
- * This function can be improved using a free list to avoid to guess
- * too much, since we could collect data about freed pages.
- *
- * note: I implemented this function just after watching an episode of
- * Battlestar Galactica, where the hybrid was continuing to say "JUMP!"
- */
-int vmFindContiguousPages(off_t *first, off_t n) {
-    off_t base, offset = 0, since_jump = 0, numfree = 0;
-
-    if (server.vm_near_pages == REDIS_VM_MAX_NEAR_PAGES) {
-        server.vm_near_pages = 0;
-        server.vm_next_page = 0;
-    }
-    server.vm_near_pages++; /* Yet another try for pages near to the old ones */
-    base = server.vm_next_page;
-
-    while(offset < server.vm_pages) {
-        off_t this = base+offset;
-
-        /* If we overflow, restart from page zero */
-        if (this >= server.vm_pages) {
-            this -= server.vm_pages;
-            if (this == 0) {
-                /* Just overflowed, what we found on tail is no longer
-                 * interesting, as it's no longer contiguous. */
-                numfree = 0;
-            }
-        }
-        if (vmFreePage(this)) {
-            /* This is a free page */
-            numfree++;
-            /* Already got N free pages? Return to the caller, with success */
-            if (numfree == n) {
-                *first = this-(n-1);
-                server.vm_next_page = this+1;
-                redisLog(REDIS_DEBUG, "FOUND CONTIGUOUS PAGES: %lld pages at %lld\n", (long long) n, (long long) *first);
-                return REDIS_OK;
-            }
-        } else {
-            /* The current one is not a free page */
-            numfree = 0;
-        }
-
-        /* Fast-forward if the current page is not free and we already
-         * searched enough near this place. */
-        since_jump++;
-        if (!numfree && since_jump >= REDIS_VM_MAX_RANDOM_JUMP/4) {
-            offset += random() % REDIS_VM_MAX_RANDOM_JUMP;
-            since_jump = 0;
-            /* Note that even if we rewind after the jump, we are don't need
-             * to make sure numfree is set to zero as we only jump *if* it
-             * is set to zero. */
-        } else {
-            /* Otherwise just check the next page */
-            offset++;
-        }
-    }
-    return REDIS_ERR;
-}
-
 /* Write the specified object at the specified page of the swap file */
 int vmWriteObjectOnSwap(robj *o, off_t page) {
     if (server.vm_enabled) pthread_mutex_lock(&server.io_swapfile_mutex);
@@ -442,89 +313,7 @@ robj *vmPreviewObject(robj *o) {
 double computeObjectSwappability(robj *o) {
     /* actual age can be >= minage, but not < minage. As we use wrapping
      * 21 bit clocks with minutes resolution for the LRU. */
-    time_t minage = estimateObjectIdleTime(o);
-    long asize = 0, elesize;
-    robj *ele;
-    list *l;
-    listNode *ln;
-    dict *d;
-    struct dictEntry *de;
-    int z;
-
-    if (minage <= 0) return 0;
-    switch(o->type) {
-    case REDIS_STRING:
-        if (o->encoding != REDIS_ENCODING_RAW) {
-            asize = sizeof(*o);
-        } else {
-            asize = sdslen(o->ptr)+sizeof(*o)+sizeof(long)*2;
-        }
-        break;
-    case REDIS_LIST:
-        if (o->encoding == REDIS_ENCODING_ZIPLIST) {
-            asize = sizeof(*o)+ziplistSize(o->ptr);
-        } else {
-            l = o->ptr;
-            ln = listFirst(l);
-            asize = sizeof(list);
-            if (ln) {
-                ele = ln->value;
-                elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(listNode)+elesize)*listLength(l);
-            }
-        }
-        break;
-    case REDIS_SET:
-    case REDIS_ZSET:
-        z = (o->type == REDIS_ZSET);
-        d = z ? ((zset*)o->ptr)->dict : o->ptr;
-
-        if (!z && o->encoding == REDIS_ENCODING_INTSET) {
-            intset *is = o->ptr;
-            asize = sizeof(*is)+is->encoding*is->length;
-        } else {
-            asize = sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
-            if (z) asize += sizeof(zset)-sizeof(dict);
-            if (dictSize(d)) {
-                de = dictGetRandomKey(d);
-                ele = dictGetEntryKey(de);
-                elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
-                if (z) asize += sizeof(zskiplistNode)*dictSize(d);
-            }
-        }
-        break;
-    case REDIS_HASH:
-        if (o->encoding == REDIS_ENCODING_ZIPMAP) {
-            unsigned char *p = zipmapRewind((unsigned char*)o->ptr);
-            unsigned int len = zipmapLen((unsigned char*)o->ptr);
-            unsigned int klen, vlen;
-            unsigned char *key, *val;
-
-            if ((p = zipmapNext(p,&key,&klen,&val,&vlen)) == NULL) {
-                klen = 0;
-                vlen = 0;
-            }
-            asize = len*(klen+vlen+3);
-        } else if (o->encoding == REDIS_ENCODING_HT) {
-            d = o->ptr;
-            asize = sizeof(dict)+(sizeof(struct dictEntry*)*dictSlots(d));
-            if (dictSize(d)) {
-                de = dictGetRandomKey(d);
-                ele = dictGetEntryKey(de);
-                elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
-                ele = dictGetEntryVal(de);
-                elesize = (ele->encoding == REDIS_ENCODING_RAW) ?
-                                (sizeof(*o)+sdslen(ele->ptr)) : sizeof(*o);
-                asize += (sizeof(struct dictEntry)+elesize)*dictSize(d);
-            }
-        }
-        break;
-    }
-    return (double)minage*log(1+asize);
+    return (double) estimateObjectIdleTime(o);
 }
 
 /* Try to swap an object that's a good candidate for swapping.
@@ -786,89 +575,6 @@ void unlockThreadedIO(void) {
     pthread_mutex_unlock(&server.io_mutex);
 }
 
-/* Remove the specified object from the threaded I/O queue if still not
- * processed, otherwise make sure to flag it as canceled. */
-void vmCancelThreadedIOJob(robj *o) {
-    list *lists[3] = {
-        server.io_newjobs,      /* 0 */
-        server.io_processing,   /* 1 */
-        server.io_processed     /* 2 */
-    };
-    int i;
-
-    redisAssert(o->storage == REDIS_VM_LOADING || o->storage == REDIS_VM_SWAPPING);
-again:
-    lockThreadedIO();
-    /* Search for a matching object in one of the queues */
-    for (i = 0; i < 3; i++) {
-        listNode *ln;
-        listIter li;
-
-        listRewind(lists[i],&li);
-        while ((ln = listNext(&li)) != NULL) {
-            iojob *job = ln->value;
-
-            if (job->canceled) continue; /* Skip this, already canceled. */
-            if (job->id == o) {
-                redisLog(REDIS_DEBUG,"*** CANCELED %p (key %s) (type %d) (LIST ID %d)\n",
-                    (void*)job, (char*)job->key->ptr, job->type, i);
-                /* Mark the pages as free since the swap didn't happened
-                 * or happened but is now discarded. */
-                if (i != 1 && job->type == REDIS_IOJOB_DO_SWAP)
-                    vmMarkPagesFree(job->page,job->pages);
-                /* Cancel the job. It depends on the list the job is
-                 * living in. */
-                switch(i) {
-                case 0: /* io_newjobs */
-                    /* If the job was yet not processed the best thing to do
-                     * is to remove it from the queue at all */
-                    freeIOJob(job);
-                    listDelNode(lists[i],ln);
-                    break;
-                case 1: /* io_processing */
-                    /* Oh Shi- the thread is messing with the Job:
-                     *
-                     * Probably it's accessing the object if this is a
-                     * PREPARE_SWAP or DO_SWAP job.
-                     * If it's a LOAD job it may be reading from disk and
-                     * if we don't wait for the job to terminate before to
-                     * cancel it, maybe in a few microseconds data can be
-                     * corrupted in this pages. So the short story is:
-                     *
-                     * Better to wait for the job to move into the
-                     * next queue (processed)... */
-
-                    /* We try again and again until the job is completed. */
-                    unlockThreadedIO();
-                    /* But let's wait some time for the I/O thread
-                     * to finish with this job. After all this condition
-                     * should be very rare. */
-                    usleep(1);
-                    goto again;
-                case 2: /* io_processed */
-                    /* The job was already processed, that's easy...
-                     * just mark it as canceled so that we'll ignore it
-                     * when processing completed jobs. */
-                    job->canceled = 1;
-                    break;
-                }
-                /* Finally we have to adjust the storage type of the object
-                 * in order to "UNDO" the operaiton. */
-                if (o->storage == REDIS_VM_LOADING)
-                    o->storage = REDIS_VM_SWAPPED;
-                else if (o->storage == REDIS_VM_SWAPPING)
-                    o->storage = REDIS_VM_MEMORY;
-                unlockThreadedIO();
-                redisLog(REDIS_DEBUG,"*** DONE");
-                return;
-            }
-        }
-    }
-    unlockThreadedIO();
-    printf("Not found: %p\n", (void*)o);
-    redisAssert(1 != 1); /* We should never reach this */
-}
-
 void *IOThreadEntryPoint(void *arg) {
     iojob *j;
     listNode *ln;
@@ -971,18 +677,6 @@ void waitEmptyIOJobsQueue(void) {
     }
 }
 
-void vmReopenSwapFile(void) {
-    /* Note: we don't close the old one as we are in the child process
-     * and don't want to mess at all with the original file object. */
-    server.vm_fp = fopen(server.vm_swap_file,"r+b");
-    if (server.vm_fp == NULL) {
-        redisLog(REDIS_WARNING,"Can't re-open the VM swap file: %s. Exiting.",
-            server.vm_swap_file);
-        _exit(1);
-    }
-    server.vm_fd = fileno(server.vm_fp);
-}
-
 /* This function must be called while with threaded IO locked */
 void queueIOJob(iojob *j) {
     redisLog(REDIS_DEBUG,"Queued IO Job %p type %d about key '%s'\n",