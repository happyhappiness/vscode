
    /* If this is a master, we want all the slaveof config options
     * in the file to be removed. */
    if (server.masterhost == NULL) {
        rewriteConfigMarkAsProcessed(state,"slaveof");
        return;
    }
    line = sdscatprintf(sdsempty(),"%s %s %d", option,
        server.masterhost, server.masterport);
    rewriteConfigRewriteLine(state,option,line,1);
