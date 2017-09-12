        }
        /* Post process it in the main thread, as there are things we
         * can do just here to avoid race conditions and/or invasive locks */
        de = dictFind(j->db->dict,j->key);
        assert(de != NULL);
        key = dictGetEntryKey(de);
