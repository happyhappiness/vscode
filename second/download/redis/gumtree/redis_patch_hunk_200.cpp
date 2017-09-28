 
     force = value != def_val;
     line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
-/* Rewrite the syslog-fability option. */
+/* Rewrite the syslog-facility option. */
 void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
     int value = server.syslog_facility, j;
     int force = value != LOG_LOCAL0;
     char *name = NULL, *option = "syslog-facility";
     sds line;
 
