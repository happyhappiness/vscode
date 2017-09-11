@@ -284,7 +284,6 @@ static void cliIntegrateHelp(void) {
                 break;
         }
         if (i != helpEntriesLen) continue;
-        printf("%s\n", cmdname);
 
         helpEntriesLen++;
         helpEntries = zrealloc(helpEntries,sizeof(helpEntry)*helpEntriesLen);
@@ -314,8 +313,6 @@ static void cliIntegrateHelp(void) {
         new->org = ch;
     }
     freeReplyObject(reply);
-
-    printf("%s\n", helpEntries[80].full);
 }
 
 /* Output command help to stdout. */
@@ -2594,13 +2591,16 @@ int main(int argc, char **argv) {
     else
         config.output = OUTPUT_STANDARD;
     config.mb_delim = sdsnew("\n");
-    cliInitHelp();
-    cliIntegrateHelp();
 
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;
     argv += firstarg;
 
+    /* Initialize the help and, if possible, use the COMMAND command in order
+     * to retrieve missing entries. */
+    cliInitHelp();
+    cliIntegrateHelp();
+
     /* Latency mode */
     if (config.latency_mode) {
         if (cliConnect(0) == REDIS_ERR) exit(1);