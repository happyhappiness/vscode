        de = dictFind(cc->db->dict, key->ptr);
        if (de) {
            val = dictGetVal(de);
            serverLog(LL_WARNING,"key '%s' found in DB containing the following object:", (char*)key->ptr);
            serverLogObjectDebugInfo(val);
        }
        decrRefCount(key);
