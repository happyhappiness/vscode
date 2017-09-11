@@ -31,6 +31,22 @@
 
 #include "redis.h"
 
+static struct {
+    const char     *name;
+    const int       value;
+} validSyslogFacilities[] = {
+    {"user",    LOG_USER},
+    {"local0",  LOG_LOCAL0},
+    {"local1",  LOG_LOCAL1},
+    {"local2",  LOG_LOCAL2},
+    {"local3",  LOG_LOCAL3},
+    {"local4",  LOG_LOCAL4},
+    {"local5",  LOG_LOCAL5},
+    {"local6",  LOG_LOCAL6},
+    {"local7",  LOG_LOCAL7},
+    {NULL, 0}
+};
+
 /*-----------------------------------------------------------------------------
  * Config file parsing
  *----------------------------------------------------------------------------*/
@@ -164,21 +180,6 @@ void loadServerConfigFromString(char *config) {
             if (server.syslog_ident) zfree(server.syslog_ident);
             server.syslog_ident = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"syslog-facility") && argc == 2) {
-            struct {
-                const char     *name;
-                const int       value;
-            } validSyslogFacilities[] = {
-                {"user",    LOG_USER},
-                {"local0",  LOG_LOCAL0},
-                {"local1",  LOG_LOCAL1},
-                {"local2",  LOG_LOCAL2},
-                {"local3",  LOG_LOCAL3},
-                {"local4",  LOG_LOCAL4},
-                {"local5",  LOG_LOCAL5},
-                {"local6",  LOG_LOCAL6},
-                {"local7",  LOG_LOCAL7},
-                {NULL, 0}
-            };
             int i;
 
             for (i = 0; validSyslogFacilities[i].name; i++) {
@@ -1298,9 +1299,33 @@ void rewriteConfigEnumOption(struct rewriteConfigState *state, char *option, int
 }
 
 void rewriteConfigSyslogfacilityOption(struct rewriteConfigState *state) {
+    int value = server.syslog_facility, j;
+    int force = value != LOG_LOCAL0;
+    char *name, *option = "syslog-facility";
+    sds line;
+
+    for (j = 0; validSyslogFacilities[j].name; j++) {
+        if (validSyslogFacilities[j].value == value) {
+            name = (char*) validSyslogFacilities[j].name;
+            break;
+        }
+    }
+    line = sdscatprintf(sdsempty(),"%s %s",option,name);
+    rewriteConfigRewriteLine(state,option,line,force);
 }
 
 void rewriteConfigSaveOption(struct rewriteConfigState *state) {
+    int j;
+    sds line;
+
+    /* Note that if there are no save parameters at all, all the current
+     * config line with "save" will be detected as orphaned and deleted,
+     * resulting into no RDB persistence as expected. */
+    for (j = 0; j < server.saveparamslen; j++) {
+        line = sdscatprintf(sdsempty(),"save %ld %d",
+            server.saveparams[j].seconds, server.saveparams[j].changes);
+        rewriteConfigRewriteLine(state,"save",line,1);
+    }
 }
 
 void rewriteConfigDirOption(struct rewriteConfigState *state) {