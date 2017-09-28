    int force = value != defvalue;
    sds line = sdscatprintf(sdsempty(),"%s %o",option,value);

    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite an enumeration option. It takes as usually state and option name,
 * and in addition the enumeration array and the default value for the
 * option. */
void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, configEnum *ce, int defval) {
    sds line;
    const char *name = configEnumGetNameOrUnknown(ce,value);
    int force = value != defval;

    line = sdscatprintf(sdsempty(),"%s %s",option,name);
    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite the syslog-facility option. */
void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
    int value = server.syslog_facility;
    int force = value != LOG_LOCAL0;
    const char *name = NULL, *option = "syslog-facility";
    sds line;

    name = configEnumGetNameOrUnknown(syslog_facility_enum,value);
    line = sdscatprintf(sdsempty(),"%s %s",option,name);
    rewriteConfigRewriteLine(state,option,line,force);
}

/* Rewrite the save option. */
void rewriteConfigSaveOption(struct rewriteConfigState *state) {
