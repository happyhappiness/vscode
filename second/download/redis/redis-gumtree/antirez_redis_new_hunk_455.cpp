#endif

void debugCommand(client *c) {
    if (c->argc == 1) {
        addReplyError(c,"You must specify a subcommand for DEBUG. Try DEBUG HELP for info.");
        return;
    }

    if (!strcasecmp(c->argv[1]->ptr,"help")) {
        void *blenp = addDeferredMultiBulkLength(c);
        int blen = 0;
        blen++; addReplyStatus(c,
        "DEBUG <subcommand> arg arg ... arg. Subcommands:");
        blen++; addReplyStatus(c,
        "segfault -- Crash the server with sigsegv.");
        blen++; addReplyStatus(c,
        "restart  -- Graceful restart: save config, db, restart.");
        blen++; addReplyStatus(c,
        "crash-and-recovery <milliseconds> -- Hard crash and restart after <milliseconds> delay.");
        blen++; addReplyStatus(c,
        "assert   -- Crash by assertion failed.");
        blen++; addReplyStatus(c,
        "reload   -- Save the RDB on disk and reload it back in memory.");
        blen++; addReplyStatus(c,
        "loadaof  -- Flush the AOF buffers on disk and reload the AOF in memory.");
        blen++; addReplyStatus(c,
        "object <key> -- Show low level info about key and associated value.");
        blen++; addReplyStatus(c,
        "sdslen <key> -- Show low level SDS string info representing key and value.");
        blen++; addReplyStatus(c,
        "populate <count> [prefix] -- Create <count> string keys named key:<num>. If a prefix is specified is used instead of the 'key' prefix.");
        blen++; addReplyStatus(c,
        "digest   -- Outputs an hex signature representing the current DB content.");
        blen++; addReplyStatus(c,
        "sleep <seconds> -- Stop the server for <seconds>. Decimals allowed.");
        blen++; addReplyStatus(c,
        "set-active-expire (0|1) -- Setting it to 0 disables expiring keys in background when they are not accessed (otherwise the Redis behavior). Setting it to 1 reenables back the default.");
        blen++; addReplyStatus(c,
        "lua-always-replicate-commands (0|1) -- Setting it to 1 makes Lua replication defaulting to replicating single commands, without the script having to enable effects replication.");
        blen++; addReplyStatus(c,
        "error <string> -- Return a Redis protocol error with <string> as message. Useful for clients unit tests to simulate Redis errors.");
        blen++; addReplyStatus(c,
        "structsize -- Return the size of different Redis core C structures.");
        blen++; addReplyStatus(c,
        "htstats <dbid> -- Return hash table statistics of the specified Redis database.");
        blen++; addReplyStatus(c,
        "jemalloc info  -- Show internal jemalloc statistics.");
        blen++; addReplyStatus(c,
        "jemalloc purge -- Force jemalloc to release unused memory.");
        setDeferredMultiBulkLength(c,blenp,blen);
    } else if (!strcasecmp(c->argv[1]->ptr,"segfault")) {
        *((char*)-1) = 'x';
    } else if (!strcasecmp(c->argv[1]->ptr,"restart") ||
               !strcasecmp(c->argv[1]->ptr,"crash-and-recover"))
