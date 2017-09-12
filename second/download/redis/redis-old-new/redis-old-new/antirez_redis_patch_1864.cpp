@@ -40,14 +40,14 @@
 #include <sys/stat.h>
 #include <sys/time.h>
 
-#include "anet.h"
+#include "hiredis.h"
 #include "sds.h"
-#include "adlist.h"
 #include "zmalloc.h"
 #include "linenoise.h"
 
 #define REDIS_NOTUSED(V) ((void) V)
 
+static redisContext *context;
 static struct config {
     char *hostip;
     int hostport;
@@ -66,7 +66,6 @@ static struct config {
     char *historyfile;
 } config;
 
-static int cliReadReply(int fd);
 static void usage();
 
 /*------------------------------------------------------------------------------
@@ -83,197 +82,156 @@ static long long mstime(void) {
     return mst;
 }
 
-static void printStringRepr(char *s, int len) {
-    printf("\"");
-    while(len--) {
-        switch(*s) {
-        case '\\':
-        case '"':
-            printf("\\%c",*s);
-            break;
-        case '\n': printf("\\n"); break;
-        case '\r': printf("\\r"); break;
-        case '\t': printf("\\t"); break;
-        case '\a': printf("\\a"); break;
-        case '\b': printf("\\b"); break;
-        default:
-            if (isprint(*s))
-                printf("%c",*s);
-            else
-                printf("\\x%02x",(unsigned char)*s);
-            break;
-        }
-        s++;
-    }
-    printf("\"");
-}
-
 /*------------------------------------------------------------------------------
  * Networking / parsing
  *--------------------------------------------------------------------------- */
 
+/* Send AUTH command to the server */
+static int cliAuth() {
+    redisReply *reply;
+    if (config.auth == NULL) return REDIS_OK;
+
+    reply = redisCommand(context,"AUTH %s",config.auth);
+    if (reply != NULL) {
+        freeReplyObject(reply);
+        return REDIS_OK;
+    }
+    return REDIS_ERR;
+}
+
+/* Send SELECT dbnum to the server */
+static int cliSelect() {
+    redisReply *reply;
+    char dbnum[16];
+    if (config.dbnum == 0) return REDIS_OK;
+
+    snprintf(dbnum,sizeof(dbnum),"%d",config.dbnum);
+    reply = redisCommand(context,"SELECT %s",dbnum);
+    if (reply != NULL) {
+        freeReplyObject(reply);
+        return REDIS_OK;
+    }
+    return REDIS_ERR;
+}
+
 /* Connect to the client. If force is not zero the connection is performed
  * even if there is already a connected socket. */
 static int cliConnect(int force) {
-    char err[ANET_ERR_LEN];
-    static int fd = ANET_ERR;
+    if (context == NULL || force) {
+        if (context != NULL)
+            redisFree(context);
 
-    if (fd == ANET_ERR || force) {
-        if (force) close(fd);
         if (config.hostsocket == NULL) {
-            fd = anetTcpConnect(err,config.hostip,config.hostport);
+            context = redisConnect(config.hostip,config.hostport);
         } else {
-            fd = anetUnixConnect(err,config.hostsocket);
+            context = redisConnectUnix(config.hostsocket);
         }
-        if (fd == ANET_ERR) {
+
+        if (context->err) {
             fprintf(stderr,"Could not connect to Redis at ");
             if (config.hostsocket == NULL)
-                fprintf(stderr,"%s:%d: %s",config.hostip,config.hostport,err);
+                fprintf(stderr,"%s:%d: %s\n",config.hostip,config.hostport,context->errstr);
             else
-                fprintf(stderr,"%s: %s",config.hostsocket,err);
-            return -1;
+                fprintf(stderr,"%s: %s\n",config.hostsocket,context->errstr);
+            redisFree(context);
+            context = NULL;
+            return REDIS_ERR;
         }
-        anetTcpNoDelay(NULL,fd);
-    }
-    return fd;
-}
-
-static sds cliReadLine(int fd) {
-    sds line = sdsempty();
 
-    while(1) {
-        char c;
-        ssize_t ret;
-
-        ret = read(fd,&c,1);
-        if (ret <= 0) {
-            sdsfree(line);
-            return NULL;
-        } else if ((ret == 0) || (c == '\n')) {
-            break;
-        } else {
-            line = sdscatlen(line,&c,1);
-        }
+        /* Do AUTH and select the right DB. */
+        if (cliAuth() != REDIS_OK)
+            return REDIS_ERR;
+        if (cliSelect() != REDIS_OK)
+            return REDIS_ERR;
     }
-    return sdstrim(line,"\r\n");
+    return REDIS_OK;
 }
 
-static int cliReadSingleLineReply(int fd, int quiet) {
-    sds reply = cliReadLine(fd);
-
-    if (reply == NULL) return 1;
-    if (!quiet)
-        printf("%s", reply);
-    sdsfree(reply);
-    return 0;
+static void cliPrintContextErrorAndExit() {
+    if (context == NULL) return;
+    fprintf(stderr,"Error: %s\n",context->errstr);
+    exit(1);
 }
 
-static int cliReadBulkReply(int fd) {
-    sds replylen = cliReadLine(fd);
-    char *reply, crlf[2];
-    int bulklen;
-
-    if (replylen == NULL) return 1;
-    bulklen = atoi(replylen);
-    if (bulklen == -1) {
-        sdsfree(replylen);
-        printf("(nil)\n");
-        return 0;
-    }
-    reply = zmalloc(bulklen);
-    anetRead(fd,reply,bulklen);
-    anetRead(fd,crlf,2);
-    if (config.raw_output || !config.tty) {
-        if (bulklen && fwrite(reply,bulklen,1,stdout) == 0) {
-            zfree(reply);
-            return 1;
+static sds cliFormatReply(redisReply *r, char *prefix) {
+    sds out = sdsempty();
+    switch (r->type) {
+    case REDIS_REPLY_ERROR:
+        out = sdscat(out,prefix);
+        if (config.tty) out = sdscat(out,"(error) ");
+        out = sdscatprintf(out,"%s\n", r->str);
+    break;
+    case REDIS_REPLY_STATUS:
+        out = sdscat(out,prefix);
+        out = sdscat(out,r->str);
+        out = sdscat(out,"\n");
+    break;
+    case REDIS_REPLY_INTEGER:
+        out = sdscat(out,prefix);
+        if (config.tty) out = sdscat(out,"(integer) ");
+        out = sdscatprintf(out,"%lld\n",r->integer);
+    break;
+    case REDIS_REPLY_STRING:
+        out = sdscat(out,prefix);
+        if (config.raw_output || !config.tty) {
+            out = sdscatlen(out,r->str,r->len);
+        } else {
+            /* If you are producing output for the standard output we want
+             * a more interesting output with quoted characters and so forth */
+            out = sdscatrepr(out,r->str,r->len);
+            out = sdscat(out,"\n");
         }
-    } else {
-        /* If you are producing output for the standard output we want
-         * a more interesting output with quoted characters and so forth */
-        printStringRepr(reply,bulklen);
-    }
-    zfree(reply);
-    return 0;
-}
-
-static int cliReadMultiBulkReply(int fd) {
-    sds replylen = cliReadLine(fd);
-    int elements, c = 1;
-    int retval = 0;
-
-    if (replylen == NULL) return 1;
-    elements = atoi(replylen);
-    if (elements == -1) {
-        sdsfree(replylen);
-        printf("(nil)\n");
-        return 0;
-    }
-    if (elements == 0) {
-        printf("(empty list or set)\n");
-    }
-    while(elements--) {
-        if (config.tty) printf("%d. ", c);
-        if (cliReadReply(fd)) retval = 1;
-        if (elements) printf("%c",config.mb_sep);
-        c++;
-    }
-    return retval;
-}
-
-static int cliReadReply(int fd) {
-    char type;
-    int nread;
-
-    if ((nread = anetRead(fd,&type,1)) <= 0) {
-        if (config.shutdown) return 0;
-        if (config.interactive &&
-            (nread == 0 || (nread == -1 && errno == ECONNRESET)))
-        {
-            return ECONNRESET;
+    break;
+    case REDIS_REPLY_NIL:
+        out = sdscat(out,prefix);
+        out = sdscat(out,"(nil)\n");
+    break;
+    case REDIS_REPLY_ARRAY:
+        if (r->elements == 0) {
+            out = sdscat(out,prefix);
+            out = sdscat(out,"(empty list or set)\n");
         } else {
-            printf("I/O error while reading from socket: %s",strerror(errno));
-            exit(1);
+            unsigned int i;
+            sds tmp;
+
+            for (i = 0; i < r->elements; i++) {
+                tmp = cliFormatReply(r->element[i],prefix);
+                out = sdscat(out,prefix);
+                out = sdscatlen(out,tmp,sdslen(tmp));
+                sdsfree(tmp);
+            }
         }
-    }
-    switch(type) {
-    case '-':
-        if (config.tty) printf("(error) ");
-        cliReadSingleLineReply(fd,0);
-        return 1;
-    case '+':
-        return cliReadSingleLineReply(fd,0);
-    case ':':
-        if (config.tty) printf("(integer) ");
-        return cliReadSingleLineReply(fd,0);
-    case '$':
-        return cliReadBulkReply(fd);
-    case '*':
-        return cliReadMultiBulkReply(fd);
+    break;
     default:
-        printf("protocol error, got '%c' as reply type byte", type);
-        return 1;
+        fprintf(stderr,"Unknown reply type: %d\n", r->type);
+        exit(1);
     }
+    return out;
 }
 
-static int selectDb(int fd) {
-    int retval;
-    sds cmd;
-    char type;
-
-    if (config.dbnum == 0)
-        return 0;
-
-    cmd = sdsempty();
-    cmd = sdscatprintf(cmd,"SELECT %d\r\n",config.dbnum);
-    anetWrite(fd,cmd,sdslen(cmd));
-    anetRead(fd,&type,1);
-    if (type <= 0 || type != '+') return 1;
-    retval = cliReadSingleLineReply(fd,1);
-    if (retval) {
-        return retval;
+static int cliReadReply() {
+    redisReply *reply;
+    sds out;
+
+    if (redisGetReply(context,(void**)&reply) != REDIS_OK) {
+        if (config.shutdown)
+            return REDIS_OK;
+        if (config.interactive) {
+            /* Filter cases where we should reconnect */
+            if (context->err == REDIS_ERR_IO && errno == ECONNRESET)
+                return REDIS_ERR;
+            if (context->err == REDIS_ERR_EOF)
+                return REDIS_ERR;
+        }
+        cliPrintContextErrorAndExit();
+        return REDIS_ERR; /* avoid compiler warning */
     }
-    return 0;
+
+    out = cliFormatReply(reply,"");
+    freeReplyObject(reply);
+    fwrite(out,sdslen(out),1,stdout);
+    sdsfree(out);
+    return REDIS_OK;
 }
 
 static void showInteractiveHelp(void) {
@@ -294,56 +252,41 @@ static void showInteractiveHelp(void) {
 
 static int cliSendCommand(int argc, char **argv, int repeat) {
     char *command = argv[0];
-    int fd, j, retval = 0;
-    sds cmd;
+    size_t *argvlen;
+    int j;
 
     config.raw_output = !strcasecmp(command,"info");
     if (!strcasecmp(command,"help")) {
         showInteractiveHelp();
-        return 0;
+        return REDIS_OK;
     }
     if (!strcasecmp(command,"shutdown")) config.shutdown = 1;
     if (!strcasecmp(command,"monitor")) config.monitor_mode = 1;
     if (!strcasecmp(command,"subscribe") ||
         !strcasecmp(command,"psubscribe")) config.pubsub_mode = 1;
-    if ((fd = cliConnect(0)) == -1) return 1;
 
-    /* Select db number */
-    retval = selectDb(fd);
-    if (retval) {
-        fprintf(stderr,"Error setting DB num\n");
-        return 1;
-    }
-
-    /* Build the command to send */
-    cmd = sdscatprintf(sdsempty(),"*%d\r\n",argc);
-    for (j = 0; j < argc; j++) {
-        cmd = sdscatprintf(cmd,"$%lu\r\n",
-            (unsigned long)sdslen(argv[j]));
-        cmd = sdscatlen(cmd,argv[j],sdslen(argv[j]));
-        cmd = sdscatlen(cmd,"\r\n",2);
-    }
+    /* Setup argument length */
+    argvlen = malloc(argc*sizeof(size_t));
+    for (j = 0; j < argc; j++)
+        argvlen[j] = sdslen(argv[j]);
 
     while(repeat--) {
-        anetWrite(fd,cmd,sdslen(cmd));
+        redisAppendCommandArgv(context,argc,(const char**)argv,argvlen);
         while (config.monitor_mode) {
-            if (cliReadSingleLineReply(fd,0)) exit(1);
-            printf("\n");
+            if (cliReadReply() != REDIS_OK) exit(1);
         }
 
         if (config.pubsub_mode) {
-            printf("Reading messages... (press Ctrl-c to quit)\n");
+            printf("Reading messages... (press Ctrl-C to quit)\n");
             while (1) {
-                cliReadReply(fd);
-                printf("\n\n");
+                if (cliReadReply() != REDIS_OK) exit(1);
             }
         }
 
-        retval = cliReadReply(fd);
-        if (!config.raw_output && config.tty) printf("\n");
-        if (retval) return retval;
+        if (cliReadReply() != REDIS_OK)
+            return REDIS_ERR;
     }
-    return 0;
+    return REDIS_OK;
 }
 
 /*------------------------------------------------------------------------------
@@ -357,12 +300,7 @@ static int parseOptions(int argc, char **argv) {
         int lastarg = i==argc-1;
 
         if (!strcmp(argv[i],"-h") && !lastarg) {
-            char *ip = zmalloc(32);
-            if (anetResolve(NULL,argv[i+1],ip) == ANET_ERR) {
-                printf("Can't resolve %s\n", argv[i]);
-                exit(1);
-            }
-            config.hostip = ip;
+            config.hostip = argv[i+1];
             i++;
         } else if (!strcmp(argv[i],"-h") && lastarg) {
             usage();
@@ -463,17 +401,18 @@ static void repl() {
                 {
                     exit(0);
                 } else {
-                    int err;
                     long long start_time = mstime(), elapsed;
 
-                    if ((err = cliSendCommand(argc, argv, 1)) != 0) {
-                        if (err == ECONNRESET) {
-                            printf("Reconnecting... ");
-                            fflush(stdout);
-                            if (cliConnect(1) == -1) exit(1);
-                            printf("OK\n");
-                            cliSendCommand(argc,argv,1);
-                        }
+                    if (cliSendCommand(argc,argv,1) != REDIS_OK) {
+                        printf("Reconnecting... ");
+                        fflush(stdout);
+                        if (cliConnect(1) != REDIS_OK) exit(1);
+                        printf("OK\n");
+
+                        /* If we still cannot send the command,
+                         * print error and abort. */
+                        if (cliSendCommand(argc,argv,1) != REDIS_OK)
+                            cliPrintContextErrorAndExit();
                     }
                     elapsed = mstime()-start_time;
                     if (elapsed > 500) printf("%.2f seconds\n",
@@ -533,19 +472,8 @@ int main(int argc, char **argv) {
     argc -= firstarg;
     argv += firstarg;
 
-    if (config.auth != NULL) {
-        char *authargv[2];
-        int dbnum = config.dbnum;
-
-        /* We need to save the real configured database number and set it to
-         * zero here, otherwise cliSendCommand() will try to perform the
-         * SELECT command before the authentication, and it will fail. */
-        config.dbnum = 0;
-        authargv[0] = "AUTH";
-        authargv[1] = config.auth;
-        cliSendCommand(2, convertToSds(2, authargv), 1);
-        config.dbnum = dbnum; /* restore the right DB number */
-    }
+    /* Try to connect */
+    if (cliConnect(0) != REDIS_OK) exit(1);
 
     /* Start interactive mode when no command is provided */
     if (argc == 0) repl();