        de = dictFind(j->db->dict,j->key->ptr);
        redisAssert(de != NULL);
        if (j->type == REDIS_IOJOB_LOAD) {
            redisDb *db;
            vmpointer *vp = dictGetEntryVal(de);

            /* Key loaded, bring it at home */
            vmMarkPagesFree(vp->page,vp->usedpages);
            redisLog(REDIS_DEBUG, "VM: object %s loaded from disk (threaded)",
                (unsigned char*) j->key->ptr);
            server.vm_stats_swapped_objects--;
            server.vm_stats_swapins++;
            dictGetEntryVal(de) = j->val;
            incrRefCount(j->val);
            db = j->db;
            /* Handle clients waiting for this key to be loaded. */
            handleClientsBlockedOnSwappedKey(db,j->key);
            freeIOJob(j);
            zfree(vp);
        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
            vmpointer *vp;

            /* Key swapped. We can finally free some memory. */
            if (j->val->storage != REDIS_VM_SWAPPING) {
                vmpointer *vp = (vmpointer*) j->id;
                printf("storage: %d\n",vp->storage);
                printf("key->name: %s\n",(char*)j->key->ptr);
                printf("val: %p\n",(void*)j->val);
                printf("val->type: %d\n",j->val->type);
                printf("val->ptr: %s\n",(char*)j->val->ptr);
            }
            redisAssert(j->val->storage == REDIS_VM_SWAPPING);
            vp = createVmPointer(j->val->type);
            vp->page = j->page;
            vp->usedpages = j->pages;
            dictGetEntryVal(de) = vp;
            /* Fix the storage otherwise decrRefCount will attempt to
             * remove the associated I/O job */
            j->val->storage = REDIS_VM_MEMORY;
            decrRefCount(j->val);
            redisLog(REDIS_DEBUG,
                "VM: object %s swapped out at %lld (%lld pages) (threaded)",
                (unsigned char*) j->key->ptr,
                (unsigned long long) j->page, (unsigned long long) j->pages);
            server.vm_stats_swapped_objects++;
            server.vm_stats_swapouts++;
            freeIOJob(j);
            /* Put a few more swap requests in queue if we are still
             * out of memory */
            if (trytoswap && vmCanSwapOut() &&
                zmalloc_used_memory() > server.vm_max_memory)
            {
                int more = 1;
                while(more) {
                    lockThreadedIO();
                    more = listLength(server.io_newjobs) <
                            (unsigned) server.vm_max_threads;
                    unlockThreadedIO();
                    /* Don't waste CPU time if swappable objects are rare. */
                    if (vmSwapOneObjectThreaded() == REDIS_ERR) {
                        trytoswap = 0;
                        break;
                    }
                }
            }
        }
        processed++;
        if (processed == toprocess) return;
