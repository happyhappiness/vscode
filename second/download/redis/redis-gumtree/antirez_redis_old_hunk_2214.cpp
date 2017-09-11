    rewriteConfigRewriteLine(state,option,line,1);
}

/* Rewrite the appendonly option. */
void rewriteConfigAppendonlyOption(struct rewriteConfigState *state) {
    int force = server.aof_state != REDIS_AOF_OFF;
    char *option = "appendonly";
    sds line;
    
    line = sdscatprintf(sdsempty(),"%s %s", option,
        (server.aof_state == REDIS_AOF_OFF) ? "no" : "yes");
    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite the notify-keyspace-events option. */
void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
    int force = server.notify_keyspace_events != 0;
