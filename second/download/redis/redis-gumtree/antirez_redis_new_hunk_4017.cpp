                unlockThreadedIO();
            }
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
