                delta = (long long) zmalloc_used_memory();
                dbDelete(db,keyobj);
                delta -= (long long) zmalloc_used_memory();
                // printf("%lld\n",delta);
                mem_freed += delta;
                server.stat_evictedkeys++;
                decrRefCount(keyobj);
