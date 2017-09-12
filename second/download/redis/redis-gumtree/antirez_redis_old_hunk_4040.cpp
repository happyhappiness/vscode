                unlockThreadedIO();
            }
        } else if (j->type == REDIS_IOJOB_DO_SWAP) {
            robj *val;

            /* Key swapped. We can finally free some memory. */
            if (key->storage != REDIS_VM_SWAPPING) {
                printf("key->storage: %d\n",key->storage);
                printf("key->name: %s\n",(char*)key->ptr);
                printf("key->refcount: %d\n",key->refcount);
                printf("val: %p\n",(void*)j->val);
                printf("val->type: %d\n",j->val->type);
                printf("val->ptr: %s\n",(char*)j->val->ptr);
            }
            redisAssert(key->storage == REDIS_VM_SWAPPING);
            val = dictGetEntryVal(de);
            key->vm.page = j->page;
            key->vm.usedpages = j->pages;
            key->storage = REDIS_VM_SWAPPED;
            key->vtype = j->val->type;
            decrRefCount(val); /* Deallocate the object from memory. */
            dictGetEntryVal(de) = NULL;
            redisLog(REDIS_DEBUG,
                "VM: object %s swapped out at %lld (%lld pages) (threaded)",
                (unsigned char*) key->ptr,
                (unsigned long long) j->page, (unsigned long long) j->pages);
            server.vm_stats_swapped_objects++;
            server.vm_stats_swapouts++;
