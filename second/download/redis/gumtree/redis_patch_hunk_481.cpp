     int force = value != defvalue;
     sds line = sdscatprintf(sdsempty(),"%s %o",option,value);
 
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
-/* Rewrite an enumeration option, after the "value" every enum/value pair
- * is specified, terminated by NULL. After NULL the default value is
- * specified. See how the function is used for more information. */
-void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, ...) {
-    va_list ap;
-    char *enum_name, *matching_name = NULL;
-    int enum_val, def_val, force;
+/* Rewrite an enumeration option. It takes as usually state and option name,
+ * and in addition the enumeration array and the default value for the
+ * option. */
+void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int value, configEnum *ce, int defval) {
     sds line;
+    const char *name = configEnumGetNameOrUnknown(ce,value);
+    int force = value != defval;
 
-    va_start(ap, value);
-    while(1) {
-        enum_name = va_arg(ap,char*);
-        enum_val = va_arg(ap,int);
-        if (enum_name == NULL) {
-            def_val = enum_val;
-            break;
-        }
-        if (value == enum_val) matching_name = enum_name;
-    }
-    va_end(ap);
-
-    force = value != def_val;
-    line = sdscatprintf(sdsempty(),"%s %s",option,matching_name);
+    line = sdscatprintf(sdsempty(),"%s %s",option,name);
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
 /* Rewrite the syslog-facility option. */
 void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
-    int value = server.syslog_facility, j;
+    int value = server.syslog_facility;
     int force = value != LOG_LOCAL0;
-    char *name = NULL, *option = "syslog-facility";
+    const char *name = NULL, *option = "syslog-facility";
     sds line;
 
-    for (j = 0; validSyslogFacilities[j].name; j++) {
-        if (validSyslogFacilities[j].value == value) {
-            name = (char*) validSyslogFacilities[j].name;
-            break;
-        }
-    }
+    name = configEnumGetNameOrUnknown(syslog_facility_enum,value);
     line = sdscatprintf(sdsempty(),"%s %s",option,name);
     rewriteConfigRewriteLine(state,option,line,force);
 }
 
 /* Rewrite the save option. */
 void rewriteConfigSaveOption(struct rewriteConfigState *state) {
