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
