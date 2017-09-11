    } else if (!strcasecmp(c->argv[1]->ptr,"set")) {
        if (c->argc < 3 || c->argc % 2 == 0) goto numargserr;
        sentinelSetCommand(c);
    } else if (!strcasecmp(c->argv[1]->ptr,"info-cache")) {
        if (c->argc < 2) goto numargserr;
        /* Reply format:
         *   1.) master name
         *   2.) 1.) info from master
         *       2.) info from replica
         *       .
         *       .
         *   3.) next master name ...
         *   4.) 1.) info from master
         *       2.) info from replica
         *       .
         *       .
         */
        dictType copy_keeper = instancesDictType;
        copy_keeper.valDestructor = NULL;
        dict *masters_local = NULL;
        int needs_cleanup = 0;
        if (c->argc == 2) {
            masters_local = sentinel.masters;
        } else {
            masters_local = dictCreate(&copy_keeper, NULL);
            needs_cleanup = 1;

            for (int i = 2; i < c->argc; i++) {
                sentinelRedisInstance *ri;
                ri = sentinelGetMasterByName(c->argv[i]->ptr);
                if (!ri) continue; /* ignore non-existing names */
                dictAdd(masters_local, ri->name, ri);
            }
        }

        /* Now we can iterate over individually requested masters the
         * same way we iterate over the entire sentinel->masters dict. */
        addReplyMultiBulkLen(c,dictSize(masters_local) * 2);

        dictIterator  *di;
        dictEntry *de;
        di = dictGetIterator(masters_local);
        while ((de = dictNext(di)) != NULL) {
            sentinelRedisInstance *ri = dictGetVal(de);
            addReplyBulkCBuffer(c,ri->name,strlen(ri->name));
            addReplyMultiBulkLen(c,dictSize(ri->slaves) + 1); /* +1 for self */
            if (ri->info)
                addReplyBulkCBuffer(c,ri->info,sdslen(ri->info));
            else
                addReply(c,shared.nullbulk);

            dictIterator *sdi;
            dictEntry *sde;
            sdi = dictGetIterator(ri->slaves);
            while ((sde = dictNext(sdi)) != NULL) {
                sentinelRedisInstance *sri = dictGetVal(sde);
                if (sri->info)
                    addReplyBulkCBuffer(c,sri->info,sdslen(sri->info));
                else
                    addReply(c,shared.nullbulk);
            }
            dictReleaseIterator(sdi);
        }
        dictReleaseIterator(di);
        if (needs_cleanup) dictRelease(masters_local);
    } else {
        addReplyErrorFormat(c,"Unknown sentinel subcommand '%s'",
                               (char*)c->argv[1]->ptr);
