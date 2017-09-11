        de = dictFind(cc->db->dict, key->ptr);
        if (de) {
            val = dictGetVal(de);
            redisLog(REDIS_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
            redisLogObjectDebugInfo(val);
        }
        decrRefCount(key);
    }
