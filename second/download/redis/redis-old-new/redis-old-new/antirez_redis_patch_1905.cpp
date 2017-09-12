@@ -36,6 +36,8 @@
 #include <stdlib.h>
 #include <unistd.h>
 #include <ctype.h>
+#include <errno.h>
+#include <sys/stat.h>
 
 #include "anet.h"
 #include "sds.h"
@@ -55,32 +57,33 @@ static struct config {
     char *hostsocket;
     long repeat;
     int dbnum;
-    int argn_from_stdin;
     int interactive;
     int shutdown;
     int monitor_mode;
     int pubsub_mode;
-    int raw_output;
+    int raw_output; /* output mode per command */
+    int tty; /* flag for default output format */
+    int stdinarg; /* get last arg from stdin. (-x option) */
+    char mb_sep;
     char *auth;
     char *historyfile;
 } config;
 
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
         if (config.hostsocket == NULL) {
             fd = anetTcpConnect(err,config.hostip,config.hostport);
         } else {
             fd = anetUnixConnect(err,config.hostsocket);
-            if (fd == ANET_ERR) {
-                fprintf(stderr, "Could not connect to Redis at %s: %s", config.hostsocket, err);
-                return -1;
-            }
         }
         if (fd == ANET_ERR) {
             fprintf(stderr,"Could not connect to Redis at ");
@@ -103,7 +106,7 @@ static sds cliReadLine(int fd) {
         ssize_t ret;
 
         ret = read(fd,&c,1);
-        if (ret == -1) {
+        if (ret <= 0) {
             sdsfree(line);
             return NULL;
         } else if ((ret == 0) || (c == '\n')) {
@@ -120,7 +123,7 @@ static int cliReadSingleLineReply(int fd, int quiet) {
 
     if (reply == NULL) return 1;
     if (!quiet)
-        printf("%s\n", reply);
+        printf("%s", reply);
     sdsfree(reply);
     return 0;
 }
@@ -147,7 +150,7 @@ static void printStringRepr(char *s, int len) {
         }
         s++;
     }
-    printf("\"\n");
+    printf("\"");
 }
 
 static int cliReadBulkReply(int fd) {
@@ -165,7 +168,7 @@ static int cliReadBulkReply(int fd) {
     reply = zmalloc(bulklen);
     anetRead(fd,reply,bulklen);
     anetRead(fd,crlf,2);
-    if (config.raw_output || !isatty(fileno(stdout))) {
+    if (config.raw_output || !config.tty) {
         if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
             zfree(reply);
             return 1;
@@ -182,6 +185,7 @@ static int cliReadBulkReply(int fd) {
 static int cliReadMultiBulkReply(int fd) {
     sds replylen = cliReadLine(fd);
     int elements, c = 1;
+    int retval = 0;
 
     if (replylen == NULL) return 1;
     elements = atoi(replylen);
@@ -194,36 +198,45 @@ static int cliReadMultiBulkReply(int fd) {
         printf("(empty list or set)\n");
     }
     while(elements--) {
-        printf("%d. ", c);
-        if (cliReadReply(fd)) return 1;
+        if (config.tty) printf("%d. ", c);
+        if (cliReadReply(fd)) retval = 1;
+        if (elements) printf("%c",config.mb_sep);
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
-        printf("(error) ");
+        if (config.tty) printf("(error) ");
         cliReadSingleLineReply(fd,0);
         return 1;
     case '+':
         return cliReadSingleLineReply(fd,0);
     case ':':
-        printf("(integer) ");
+        if (config.tty) printf("(integer) ");
         return cliReadSingleLineReply(fd,0);
     case '$':
         return cliReadBulkReply(fd);
     case '*':
         return cliReadMultiBulkReply(fd);
     default:
-        printf("protocol error, got '%c' as reply type byte\n", type);
+        printf("protocol error, got '%c' as reply type byte", type);
         return 1;
     }
 }
@@ -248,17 +261,37 @@ static int selectDb(int fd) {
     return 0;
 }
 
+static void showInteractiveHelp(void) {
+    printf(
+    "\n"
+    "Welcome to redis-cli " REDIS_VERSION "!\n"
+    "Just type any valid Redis command to see a pretty printed output.\n"
+    "\n"
+    "It is possible to quote strings, like in:\n"
+    "  set \"my key\" \"some string \\xff\\n\"\n"
+    "\n"
+    "You can find a list of valid Redis commands at\n"
+    "  http://code.google.com/p/redis/wiki/CommandReference\n"
+    "\n"
+    "Note: redis-cli supports line editing, use up/down arrows for history."
+    "\n\n");
+}
+
 static int cliSendCommand(int argc, char **argv, int repeat) {
     char *command = argv[0];
     int fd, j, retval = 0;
     sds cmd;
 
     config.raw_output = !strcasecmp(command,"info");
+    if (!strcasecmp(command,"help")) {
+        showInteractiveHelp();
+        return 0;
+    }
     if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
     if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(command,"subscribe") ||
         !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;
-    if ((fd = cliConnect()) == -1) return 1;
+    if ((fd = cliConnect(0)) == -1) return 1;
 
     /* Select db number */
     retval = selectDb(fd);
@@ -279,21 +312,21 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     while(repeat--) {
         anetWrite(fd,cmd,sdslen(cmd));
         while (config.monitor_mode) {
-            cliReadSingleLineReply(fd,0);
+            if (cliReadSingleLineReply(fd,0)) exit(1);
+            printf("\n");
         }
 
         if (config.pubsub_mode) {
             printf("Reading messages... (press Ctrl-c to quit)\n");
             while (1) {
                 cliReadReply(fd);
-                printf("\n");
+                printf("\n\n");
             }
         }
 
         retval = cliReadReply(fd);
-        if (retval) {
-            return retval;
-        }
+        if (!config.raw_output && config.tty) printf("\n");
+        if (retval) return retval;
     }
     return 0;
 }
@@ -314,6 +347,8 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"-h") && lastarg) {
             usage();
+        } else if (!strcmp(argv[i],"-x")) {
+            config.stdinarg = 1;
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
             i++;
@@ -330,11 +365,18 @@ static int parseOptions(int argc, char **argv) {
             config.auth = argv[i+1];
             i++;
         } else if (!strcmp(argv[i],"-i")) {
-            config.interactive = 1;
+            fprintf(stderr,
+"Starting interactive mode using -i is deprecated. Interactive mode is started\n"
+"by default when redis-cli is executed without a command to execute.\n"
+            );
         } else if (!strcmp(argv[i],"-c")) {
-            config.argn_from_stdin = 1;
+            fprintf(stderr,
+"Reading last argument from standard input using -c is deprecated.\n"
+"When standard input is connected to a pipe or regular file, it is\n"
+"automatically used as last argument.\n"
+            );
         } else if (!strcmp(argv[i],"-v")) {
-            printf("redis-cli shipped with Redis verison %s\n", REDIS_VERSION);
+            printf("redis-cli shipped with Redis version %s\n", REDIS_VERSION);
             exit(0);
         } else {
             break;
@@ -362,9 +404,8 @@ static sds readArgFromStdin(void) {
 
 static void usage() {
     fprintf(stderr, "usage: redis-cli [-iv] [-h host] [-p port] [-s /path/to/socket] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 arg3 ... argN\n");
-    fprintf(stderr, "usage: echo \"argN\" | redis-cli -c [-h host] [-p port] [-s /path/to/socket] [-a authpw] [-r repeat_times] [-n db_num] cmd arg1 arg2 ... arg(N-1)\n");
-    fprintf(stderr, "\nIf a pipe from standard input is detected this data is used as last argument.\n\n");
-    fprintf(stderr, "example: cat /etc/passwd | redis-cli set my_passwd\n");
+    fprintf(stderr, "usage: echo \"argN\" | redis-cli -x [options] cmd arg1 arg2 ... arg(N-1)\n\n");
+    fprintf(stderr, "example: cat /etc/passwd | redis-cli -x set my_passwd\n");
     fprintf(stderr, "example: redis-cli get my_passwd\n");
     fprintf(stderr, "example: redis-cli -r 100 lpush mylist x\n");
     fprintf(stderr, "\nRun in interactive mode: redis-cli -i or just don't pass any command\n");
@@ -382,87 +423,39 @@ static char **convertToSds(int count, char** args) {
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
 
+    config.interactive = 1;
     while((line = linenoise("redis> ")) != NULL) {
         if (line[0] != '\0') {
-            argv = splitArguments(line,&argc);
+            argv = sdssplitargs(line,&argc);
             linenoiseHistoryAdd(line);
             if (config.historyfile) linenoiseHistorySave(config.historyfile);
-            if (argc > 0) {
+            if (argv == NULL) {
+                printf("Invalid argument(s)\n");
+                continue;
+            } else if (argc > 0) {
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
@@ -475,23 +468,37 @@ static void repl() {
     exit(0);
 }
 
+static int noninteractive(int argc, char **argv) {
+    int retval = 0;
+    if (config.stdinarg) {
+        argv = zrealloc(argv, (argc+1)*sizeof(char*));
+        argv[argc] = readArgFromStdin();
+        retval = cliSendCommand(argc+1, argv, config.repeat);
+    } else {
+        /* stdin is probably a tty, can be tested with S_ISCHR(s.st_mode) */
+        retval = cliSendCommand(argc, argv, config.repeat);
+    }
+    return retval;
+}
+
 int main(int argc, char **argv) {
     int firstarg;
-    char **argvcopy;
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
     config.hostsocket = NULL;
     config.repeat = 1;
     config.dbnum = 0;
-    config.argn_from_stdin = 0;
-    config.shutdown = 0;
     config.interactive = 0;
+    config.shutdown = 0;
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
     config.raw_output = 0;
+    config.stdinarg = 0;
     config.auth = NULL;
     config.historyfile = NULL;
+    config.tty = isatty(fileno(stdout)) || (getenv("FAKETTY") != NULL);
+    config.mb_sep = '\n';
 
     if (getenv("HOME") != NULL) {
         config.historyfile = malloc(256);
@@ -505,19 +512,20 @@ int main(int argc, char **argv) {
 
     if (config.auth != NULL) {
         char *authargv[2];
+        int dbnum = config.dbnum;
 
+        /* We need to save the real configured database number and set it to
+         * zero here, otherwise cliSendCommand() will try to perform the
+         * SELECT command before the authentication, and it will fail. */
+        config.dbnum = 0;
         authargv[0] = "AUTH";
         authargv[1] = config.auth;
         cliSendCommand(2, convertToSds(2, authargv), 1);
+        config.dbnum = dbnum; /* restore the right DB number */
     }
 
-    if (argc == 0 || config.interactive == 1) repl();
-
-    argvcopy = convertToSds(argc+1, argv);
-    if (config.argn_from_stdin) {
-        sds lastarg = readArgFromStdin();
-        argvcopy[argc] = lastarg;
-        argc++;
-    }
-    return cliSendCommand(argc, argvcopy, config.repeat);
+    /* Start interactive mode when no command is provided */
+    if (argc == 0) repl();
+    /* Otherwise, we have some arguments to execute */
+    return noninteractive(argc,convertToSds(argc,argv));
 }