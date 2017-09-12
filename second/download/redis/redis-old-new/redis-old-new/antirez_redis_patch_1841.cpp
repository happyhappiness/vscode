@@ -44,6 +44,7 @@
 #include "sds.h"
 #include "zmalloc.h"
 #include "linenoise.h"
+#include "help.h"
 
 #define REDIS_NOTUSED(V) ((void) V)
 
@@ -252,30 +253,14 @@ static int cliReadReply() {
     return REDIS_OK;
 }
 
-static void showInteractiveHelp(void) {
-    printf(
-    "\n"
-    "Welcome to redis-cli " REDIS_VERSION "!\n"
-    "Just type any valid Redis command to see a pretty printed output.\n"
-    "\n"
-    "It is possible to quote strings, like in:\n"
-    "  set \"my key\" \"some string \\xff\\n\"\n"
-    "\n"
-    "You can find a list of valid Redis commands at\n"
-    "  http://code.google.com/p/redis/wiki/CommandReference\n"
-    "\n"
-    "Note: redis-cli supports line editing, use up/down arrows for history."
-    "\n\n");
-}
-
 static int cliSendCommand(int argc, char **argv, int repeat) {
     char *command = argv[0];
     size_t *argvlen;
     int j;
 
     config.raw_output = !strcasecmp(command,"info");
     if (!strcasecmp(command,"help")) {
-        showInteractiveHelp();
+        output_help(--argc, ++argv);
         return REDIS_OK;
     }
     if (!strcasecmp(command,"shutdown")) config.shutdown = 1;