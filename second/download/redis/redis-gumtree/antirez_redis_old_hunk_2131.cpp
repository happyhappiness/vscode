     * resulting into no RDB persistence as expected. */
    for (j = 0; j < server.saveparamslen; j++) {
        line = sdscatprintf(sdsempty(),"save %ld %d",
            server.saveparams[j].seconds, server.saveparams[j].changes);
        rewriteConfigRewriteLine(state,"save",line,1);
    }
    /* Mark "save" as processed in case server.saveparamslen is zero. */
