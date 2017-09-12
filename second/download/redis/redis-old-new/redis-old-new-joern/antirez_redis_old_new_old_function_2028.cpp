void rewriteConfigNotifykeyspaceeventsOption(struct rewriteConfigState *state) {
    int force = server.notify_keyspace_events != 0;
    char *option = "notify-keyspace-events";
    sds line, flags;

    flags = keyspaceEventsFlagsToString(server.notify_keyspace_events);
    line = sdscatprintf(sdsempty(),"%s %s", option, flags);
    sdsfree(flags);
    rewriteConfigRewriteLine(state,option,line,force);
}