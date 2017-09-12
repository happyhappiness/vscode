        de = dictFind(j->db->dict,j->key->ptr);
        redisAssert(de != NULL);
        if (j->type == REDIS_IOJOB_LOAD) {
            dbAdd(j->db,j->key,j->val);
            freeIOJob(j);
            /* FIXME: notify clients waiting for this key */
        } else if (j->type == REDIS_IOJOB_SAVE) {
            redisAssert(j->val->storage == REDIS_DS_SAVING);
            j->val->storage = REDIS_DS_MEMORY;
            freeIOJob(j);
        }
        processed++;
        if (processed == toprocess) return;
