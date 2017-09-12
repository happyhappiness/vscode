@@ -29,6 +29,7 @@
  */
 
 #include "fmacros.h"
+#include "version.h"
 
 #include <stdio.h>
 #include <string.h>
@@ -60,6 +61,7 @@ static struct config {
     int pubsub_mode;
     int raw_output;
     char *auth;
+    char *historyfile;
 } config;
 
 static int cliReadReply(int fd);
@@ -315,6 +317,9 @@ static int parseOptions(int argc, char **argv) {
             config.interactive = 1;
         } else if (!strcmp(argv[i],"-c")) {
             config.argn_from_stdin = 1;
+        } else if (!strcmp(argv[i],"-v")) {
+            printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
+            exit(0);
         } else {
             break;
         }
@@ -340,7 +345,7 @@ static sds readArgFromStdin(void) {
 }
 
 static void usage() {
-    fprintf(stderr, "usage: redis-cli [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] [-i] cmd arg1 arg2 arg3 ... argN\n");
+    fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
     fprintf(stderr, "usage: echo \"argN\" | redis-cli -c [-h host] [-p port] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
     fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
     fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
@@ -361,80 +366,17 @@ static char **convertToSds(int count, char** args) {
   return sds;
 }
 
-static char **splitArguments(char *line, int *argc) {
-    char *p = line;
-    char *current = NULL;
-    char **vector = NULL;
-
-    *argc = 0;
-    while(1) {
-        /* skip blanks */
-        while(*p && isspace(*p)) p++;
-        if (*p) {
-            /* get a token */
-            int inq=0; /* set to 1 if we are in "quotes" */
-            int done = 0;
-
-            if (current == NULL) current = sdsempty();
-            while(!done) {
-                if (inq) {
-                    if (*p == '\\' && *(p+1)) {
-                        char c;
-
-                        p++;
-                        switch(*p) {
-                        case 'n': c = '\n'; break;
-                        case 'r': c = '\r'; break;
-                        case 't': c = '\t'; break;
-                        case 'b': c = '\b'; break;
-                        case 'a': c = '\a'; break;
-                        default: c = *p; break;
-                        }
-                        current = sdscatlen(current,&c,1);
-                    } else if (*p == '"') {
-                        done = 1;
-                    } else {
-                        current = sdscatlen(current,p,1);
-                    }
-                } else {
-                    switch(*p) {
-                    case ' ':
-                    case '\n':
-                    case '\r':
-                    case '\t':
-                    case '\0':
-                        done=1;
-                        break;
-                    case '"':
-                        inq=1;
-                        break;
-                    default:
-                        current = sdscatlen(current,p,1);
-                        break;
-                    }
-                }
-                if (*p) p++;
-            }
-            /* add the token to the vector */
-            vector = zrealloc(vector,((*argc)+1)*sizeof(char*));
-            vector[*argc] = current;
-            (*argc)++;
-            current = NULL;
-        } else {
-            return vector;
-        }
-    }
-}
-
 #define LINE_BUFLEN 4096
 static void repl() {
     int argc, j;
-    char *line, **argv;
+    char *line;
+    sds *argv;
 
     while((line = linenoise("redis> ")) != NULL) {
         if (line[0] != '\0') {
-            argv = splitArguments(line,&argc);
+            argv = sdssplitargs(line,&argc);
             linenoiseHistoryAdd(line);
+            if (config.historyfile) linenoiseHistorySave(config.historyfile);
             if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||
                     strcasecmp(argv[0],"exit") == 0)
@@ -468,6 +410,13 @@ int main(int argc, char **argv) {
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