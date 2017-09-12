void rewriteConfigSaveOption(struct rewriteConfigState *state) {
    int j;
    sds line;

    /* Note that if there are no save parameters at all, all the current
     * config line with "save" will be detected as orphaned and deleted,
     * resulting into no RDB persistence as expected. */
    for (j = 0; j < server.saveparamslen; j++) {
        line = sdscatprintf(sdsempty(),"save %ld %d",
            server.saveparams[j].seconds, server.saveparams[j].changes);
        rewriteConfigRewriteLine(state,"save",line,1);
    }
}