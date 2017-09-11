                delta -= (long long) zmalloc_used_memory();
                mem_freed += delta;
                server.stat_evictedkeys++;
                notifyKeyspaceEvent("evicted",keyobj,db->id);
                decrRefCount(keyobj);
                keys_freed++;

