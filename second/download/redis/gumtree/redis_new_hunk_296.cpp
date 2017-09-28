     * resulting into no RDB persistence as expected. */
    for (j = 0; j < server.saveparamslen; j++) {
        line = sdscatprintf(sdsempty(),"save %ld %d",
            server.saveparams[j].seconds, server.saveparams[j].changes);
        rewriteConfigRewriteLine(state,"save",line,1);
    }
    /* Mark "save" as processed in case server.saveparamslen is zero. */
    rewriteConfigMarkAsProcessed(state,"save");
}

/* Rewrite the dir option, always using absolute paths.*/
void rewriteConfigDirOption(struct rewriteConfigState *state) {
    char cwd[1024];

    if (getcwd(cwd,sizeof(cwd)) == NULL) {
        rewriteConfigMarkAsProcessed(state,"dir");
        return; /* no rewrite on error. */
    }
    rewriteConfigStringOption(state,"dir",cwd,NULL);
}

/* Rewrite the slaveof option. */
void rewriteConfigSlaveofOption(struct rewriteConfigState *state) {
    char *option = "slaveof";
    sds line;

    /* If this is a master, we want all the slaveof config options
     * in the file to be removed. */
    if (server.masterhost == NULL) {
        rewriteConfigMarkAsProcessed(state,"slaveof");
        return;
    }
    line = sdscatprintf(sdsempty(),"%s %s %d", option,
        server.masterhost, server.masterport);
    rewriteConfigRewriteLine(state,option,line,1);
}

/* Rewrite the notify-keyspace-events option. */
void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
    int force = server.notify_keyspace_events != 0;
    char *option = "notify-keyspace-events";
    sds line, flags;

