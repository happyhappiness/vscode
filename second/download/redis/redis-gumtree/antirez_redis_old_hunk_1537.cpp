
/* Rewrite the syslog-facility option. */
void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
    int value = server.syslog_facility, j;
    int force = value != LOG_LOCAL0;
    char *name = NULL, *option = "syslog-facility";
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
