    if (allsections || !strcasecmp(section,"commandstats")) {
        if (sections++) info = sdscat(info,"\r\n");
        info = sdscatprintf(info, "# Commandstats\r\n");
        numcommands = sizeof(readonlyCommandTable)/sizeof(struct redisCommand);
        for (j = 0; j < numcommands; j++) {
            struct redisCommand *c = readonlyCommandTable+j;

            if (!c->microseconds) continue;
            info = sdscatprintf(info,"cmdstat_%s:calls=%lld,usec=%lld\r\n",
                c->name, c->calls, c->microseconds);
        }
    }

