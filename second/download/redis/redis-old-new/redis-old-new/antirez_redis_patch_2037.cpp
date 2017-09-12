@@ -61,6 +61,7 @@ static struct config {
     int pubsub_mode;
     int raw_output;
     char *auth;
+    char *historyfile;
 } config;
 
 static int cliReadReply(int fd);
@@ -439,6 +440,7 @@ static void repl() {
         if (line[0] != '\0') {
             argv = splitArguments(line,&argc);
             linenoiseHistoryAdd(line);
+            if (config.historyfile) linenoiseHistorySave(config.historyfile);
             if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||
                     strcasecmp(argv[0],"exit") == 0)
@@ -472,6 +474,13 @@ int main(int argc, char **argv) {
     config.pubsub_mode = 0;
     config.raw_output = 0;
     config.auth = NULL;
+    config.historyfile = NULL;
+
+    if (getenv("HOME") != NULL) {
+        config.historyfile = malloc(256);
+        snprintf(config.historyfile,256,"%s/.rediscli_history",getenv("HOME"));
+        linenoiseHistoryLoad(config.historyfile);
+    }
 
     firstarg = parseOptions(argc,argv);
     argc -= firstarg;