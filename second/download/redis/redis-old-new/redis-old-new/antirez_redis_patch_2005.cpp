@@ -36,6 +36,7 @@
 #include <stdlib.h>
 #include <unistd.h>
 #include <ctype.h>
+#include <errno.h>
 
 #include "anet.h"
 #include "sds.h"
@@ -68,11 +69,14 @@ static struct config {
 static int cliReadReply(int fd);
 static void usage();
 
-static int cliConnect(void) {
+/* Connect to the client. If force is not zero the connection is performed
+ * even if there is already a connected socket. */
+static int cliConnect(int force) {
     char err[ANET_ERR_LEN];
     static int fd = ANET_ERR;
 
-    if (fd == ANET_ERR) {
+    if (fd == ANET_ERR || force) {
+        if (force) close(fd);
         fd = anetTcpConnect(err,config.hostip,config.hostport);
         if (fd == ANET_ERR) {
             fprintf(stderr, "Could not connect to Redis at %s:%d: %s", config.hostip, config.hostport, err);
@@ -170,6 +174,7 @@ static int cliReadBulkReply(int fd) {
 static int cliReadMultiBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     int elements, c = 1;
+    int retval = 0;
 
     if (replylen == NULL) return 1;
     elements = atoi(replylen);
@@ -183,19 +188,27 @@ static int cliReadMultiBulkReply(int fd) {
     }
     while(elements--) {
         if (config.tty) printf("%d. ", c);
-        if (cliReadReply(fd)) return 1;
+        if (cliReadReply(fd)) retval = 1;
         if (elements) printf("%c",config.mb_sep);
         c++;
     }
-    return 0;
+    return retval;
 }
 
 static int cliReadReply(int fd) {
     char type;
+    int nread;
 
-    if (anetRead(fd,&type,1) <= 0) {
+    if ((nread = anetRead(fd,&type,1)) <= 0) {
         if (config.shutdown) return 0;
-        exit(1);
+        if (config.interactive &&
+            (nread == 0 || (nread == -1 && errno == ECONNRESET)))
+        {
+            return ECONNRESET;
+        } else {
+            printf("I/O error while reading from socket: %s",strerror(errno));
+            exit(1);
+        }
     }
     switch(type) {
     case '-':
@@ -247,7 +260,7 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(command,"subscribe") ||
         !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;
-    if ((fd = cliConnect()) == -1) return 1;
+    if ((fd = cliConnect(0)) == -1) return 1;
 
     /* Select db number */
     retval = selectDb(fd);
@@ -374,91 +387,15 @@ static char **convertToSds(int count, char** args) {
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
-            int done=0;
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
-                        /* closing quote must be followed by a space */
-                        if (*(p+1) && !isspace(*(p+1))) goto err;
-                        done=1;
-                    } else if (!*p) {
-                        /* unterminated quotes */
-                        goto err;
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
-
-err:
-    while(*argc--)
-        sdsfree(vector[*argc]);
-    zfree(vector);
-    if (current) sdsfree(current);
-    return NULL;
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
             if (config.historyfile) linenoiseHistorySave(config.historyfile);
             if (argv == NULL) {
@@ -467,9 +404,21 @@ static void repl() {
             } else if (argc > 0) {
                 if (strcasecmp(argv[0],"quit") == 0 ||
                     strcasecmp(argv[0],"exit") == 0)
-                        exit(0);
-                else
-                    cliSendCommand(argc, argv, 1);
+                {
+                    exit(0);
+                } else {
+                    int err;
+
+                    if ((err = cliSendCommand(argc, argv, 1)) != 0) {
+                        if (err == ECONNRESET) {
+                            printf("Reconnecting... ");
+                            fflush(stdout);
+                            if (cliConnect(1) == -1) exit(1);
+                            printf("OK\n");
+                            cliSendCommand(argc,argv,1);
+                        }
+                    }
+                }
             }
             /* Free the argument vector */
             for (j = 0; j < argc; j++)