    sds line, flags;

    flags = keyspaceEventsFlagsToString(server.notify_keyspace_events);
    line = sdscatprintf(sdsempty(),"%s %s", option, flags);
    sdsfree(flags);
    rewriteConfigRewriteLine(state,option,line,force);
}
