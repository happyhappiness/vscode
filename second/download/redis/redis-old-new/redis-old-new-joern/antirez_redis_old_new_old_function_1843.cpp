void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
    int force = server.aof_state != REDIS_AOF_OFF;
    char *option = "appendonly";
    sds line;
    
    line = sdscatprintf(sdsempty(),"%s %s", option,
        (server.aof_state == REDIS_AOF_OFF) ? "no" : "yes");
    rewriteConfigRewriteLine(state,option,line,force);
}