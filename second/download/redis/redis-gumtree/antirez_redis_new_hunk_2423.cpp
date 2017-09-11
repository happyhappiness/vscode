}

void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
    int value = server.syslog_facility, j;
    int force = value != LOG_LOCAL0;
    char *name, *option = "syslog-facility";
    sds line;

    for (j = 0; validSyslogFacilities[j].name; j++) {
        if (validSyslogFacilities[j].value == value) {
            name = (char*) validSyslogFacilities[j].name;
            break;
        }
    }
    line = sdscatprintf(sdsempty(),"%s %s",option,name);
    rewriteConfigRewriteLine(state,option,line,force);
}

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

void rewriteConfigDirOption(struct rewriteConfigState *state) {
