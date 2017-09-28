                serverLog(LL_WARNING,"WARNING: the new maxmemory value set via CONFIG SET is smaller than the current memory usage. This will result in keys eviction and/or inability to accept new write commands depending on the maxmemory-policy.");
            }
            freeMemoryIfNeeded();
        }
    } config_set_memory_field("repl-backlog-size",ll) {
        resizeReplicationBacklog(ll);
    } config_set_memory_field("auto-aof-rewrite-min-size",ll) {
        server.aof_rewrite_min_size = ll;

    /* Enumeration fields.
     * config_set_enum_field(name,var,enum_var) */
    } config_set_enum_field(
      "loglevel",server.verbosity,loglevel_enum) {
    } config_set_enum_field(
