        usage += sdsAllocSize(c->argv[1]->ptr);
        usage += sizeof(dictEntry);
        addReplyLongLong(c,usage);
    } else if (!strcasecmp(c->argv[1]->ptr,"overhead") && c->argc == 2) {
        int j;
        size_t mem_total = 0;
        size_t mem = 0;
        size_t zmalloc_used = zmalloc_used_memory();

        int toplevel_keys = 8;
        void *tlk = addDeferredMultiBulkLength(c);

        addReplyBulkCString(c,"total.allocated");
        addReplyLongLong(c,zmalloc_used);

        addReplyBulkCString(c,"startup.allocated");
        addReplyLongLong(c,server.initial_memory_usage);
        mem_total += server.initial_memory_usage;

        mem = 0;
        if (server.repl_backlog)
            mem += zmalloc_size(server.repl_backlog);
        addReplyBulkCString(c,"replication.backlog");
        addReplyLongLong(c,mem);
        mem_total += mem;

        mem = 0;
        if (listLength(server.slaves)) {
            listIter li;
            listNode *ln;

            listRewind(server.slaves,&li);
            while((ln = listNext(&li))) {
                client *client = listNodeValue(ln);
                mem += getClientOutputBufferMemoryUsage(client);
                mem += sdsAllocSize(client->querybuf);
                mem += sizeof(client);
            }
        }
        addReplyBulkCString(c,"clients.slaves");
        addReplyLongLong(c,mem);
        mem_total+=mem;

        mem = 0;
        if (listLength(server.clients)) {
            listIter li;
            listNode *ln;

            listRewind(server.clients,&li);
            while((ln = listNext(&li))) {
                client *client = listNodeValue(ln);
                if (client->flags & CLIENT_SLAVE)
                    continue;
                mem += getClientOutputBufferMemoryUsage(client);
                mem += sdsAllocSize(client->querybuf);
                mem += sizeof(client);
            }
        }
        addReplyBulkCString(c,"clients.normal");
        addReplyLongLong(c,mem);
        mem_total+=mem;

        mem = 0;
        if (server.aof_state != AOF_OFF) {
            mem += sdslen(server.aof_buf);
            mem += aofRewriteBufferSize();
        }
        addReplyBulkCString(c,"aof.buffer");
        addReplyLongLong(c,mem);
        mem_total+=mem;

        for (j = 0; j < server.dbnum; j++) {
            redisDb *db = server.db+j;
            long long keyscount = dictSize(db->dict);
            if (keyscount==0) continue;

            char dbname[32];
            toplevel_keys++;
            snprintf(dbname,sizeof(dbname),"db.%d",j);
            addReplyBulkCString(c,dbname);
            addReplyMultiBulkLen(c,4);

            mem = dictSize(db->dict) * sizeof(dictEntry) +
                  dictSlots(db->dict) * sizeof(dictEntry*) +
                  dictSize(db->dict) * sizeof(robj);
            addReplyBulkCString(c,"overhead.hashtable.main");
            addReplyLongLong(c,mem);
            mem_total+=mem;

            mem = dictSize(db->expires) * sizeof(dictEntry) +
                  dictSlots(db->expires) * sizeof(dictEntry*);
            addReplyBulkCString(c,"overhead.hashtable.expires");
            addReplyLongLong(c,mem);
            mem_total+=mem;
        }

        addReplyBulkCString(c,"overhead.total");
        addReplyLongLong(c,mem_total);

        addReplyBulkCString(c,"dataset");
        addReplyLongLong(c,zmalloc_used - mem_total);

        setDeferredMultiBulkLength(c,tlk,toplevel_keys*2);
    } else {
        addReplyError(c,"Syntax error. Try MEMORY [usage <key>] | [overhead]");
    }
}
