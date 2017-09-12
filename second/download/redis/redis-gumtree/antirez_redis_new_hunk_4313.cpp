        }
        /* Post process it in the main thread, as there are things we
         * can do just here to avoid race conditions and/or invasive locks */
        redisLog(REDIS_DEBUG,"Job type: %d, key at %p (%s) refcount: %d\n", j->type, (void*)j->key, (char*)j->key->ptr, j->key->refcount);
        if (j->key->refcount <= 0) {
            printf("Ooops ref count is <= 0!\n");
            exit(1);
        }
        de = dictFind(j->db->dict,j->key);
        assert(de != NULL);
        key = dictGetEntryKey(de);
