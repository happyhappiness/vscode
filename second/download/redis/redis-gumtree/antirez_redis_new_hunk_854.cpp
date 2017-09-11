    } config_set_memory_field("maxmemory",server.maxmemory) {
        if (server.maxmemory) {
            if (server.maxmemory < zmalloc_used_memory()) {
                serverLog(LL_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
            }
            freeMemoryIfNeeded();
        }
