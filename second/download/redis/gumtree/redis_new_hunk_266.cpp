                 * we are freeing removing the key, but we can't account for
                 * that otherwise we would never exit the loop.
                 *
                 * AOF and Output buffer memory will be freed eventually so
                 * we only care about memory used by the key space. */
                delta = (long long) zmalloc_used_memory();
                latencyStartMonitor(eviction_latency);
                dbDelete(db,keyobj);
                latencyEndMonitor(eviction_latency);
                latencyAddSampleIfNeeded("eviction-del",eviction_latency);
                latencyRemoveNestedEvent(latency,eviction_latency);
                delta -= (long long) zmalloc_used_memory();
                mem_freed += delta;
                server.stat_evictedkeys++;
                notifyKeyspaceEvent(REDIS_NOTIFY_EVICTED, "evicted",
                    keyobj, db->id);
                decrRefCount(keyobj);
