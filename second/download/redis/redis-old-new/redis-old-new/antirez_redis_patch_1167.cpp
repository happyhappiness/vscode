@@ -42,6 +42,7 @@
 #include <sys/time.h>
 #include <assert.h>
 #include <fcntl.h>
+#include <limits.h>
 
 #include "hiredis.h"
 #include "sds.h"
@@ -76,6 +77,7 @@ static struct config {
     int slave_mode;
     int pipe_mode;
     int getrdb_mode;
+    int stat_mode;
     char *rdb_filename;
     int bigkeys;
     int stdinarg; /* get last arg from stdin. (-x option) */
@@ -631,6 +633,36 @@ static int cliSendCommand(int argc, char **argv, int repeat) {
     return REDIS_OK;
 }
 
+/* Send the INFO command, reconnecting the link if needed. */
+static redisReply *reconnectingInfo(void) {
+    redisContext *c = context;
+    redisReply *reply = NULL;
+    int tries = 0;
+
+    assert(!c->err);
+    while(reply == NULL) {
+        while (c->err & (REDIS_ERR_IO | REDIS_ERR_EOF)) {
+            printf("Reconnecting (%d)...\r", ++tries);
+            fflush(stdout);
+
+            redisFree(c);
+            c = redisConnect(config.hostip,config.hostport);
+            usleep(1000000);
+        }
+
+        reply = redisCommand(c,"INFO");
+        if (c->err && !(c->err & (REDIS_ERR_IO | REDIS_ERR_EOF))) {
+            fprintf(stderr, "Error: %s\n", c->errstr);
+            exit(1);
+        } else if (tries > 0) {
+            printf("\n");
+        }
+    }
+
+    context = c;
+    return reply;
+}
+
 /*------------------------------------------------------------------------------
  * User interface
  *--------------------------------------------------------------------------- */
@@ -671,6 +703,8 @@ static int parseOptions(int argc, char **argv) {
             config.latency_mode = 1;
         } else if (!strcmp(argv[i],"--slave")) {
             config.slave_mode = 1;
+        } else if (!strcmp(argv[i],"--stat")) {
+            config.stat_mode = 1;
         } else if (!strcmp(argv[i],"--rdb") && !lastarg) {
             config.getrdb_mode = 1;
             config.rdb_filename = argv[++i];
@@ -1266,6 +1300,145 @@ static void findBigKeys(void) {
     }
 }
 
+/* Return the specified INFO field from the INFO command output "info".
+ * A new buffer is allocated for the result, that needs to be free'd.
+ * If the field is not found NULL is returned. */
+static char *getInfoField(char *info, char *field) {
+    char *p = strstr(info,field);
+    char *n1, *n2;
+    char *result;
+
+    if (!p) return NULL;
+    p += strlen(field)+1;
+    n1 = strchr(p,'\r');
+    n2 = strchr(p,',');
+    if (n2 && n2 < n1) n1 = n2;
+    result = malloc(sizeof(char)*(n1-p)+1);
+    memcpy(result,p,(n1-p));
+    result[n1-p] = '\0';
+    return result;
+}
+
+/* Like the above function but automatically convert the result into
+ * a long. On error (missing field) LONG_MIN is returned. */
+static long getLongInfoField(char *info, char *field) {
+    char *value = getInfoField(info,field);
+    long l;
+
+    if (!value) return LONG_MIN;
+    l = strtol(value,NULL,10);
+    free(value);
+    return l;
+}
+
+/* Convert number of bytes into a human readable string of the form:
+ * 100B, 2G, 100M, 4K, and so forth. */
+void bytesToHuman(char *s, long long n) {
+    double d;
+
+    if (n < 0) {
+        *s = '-';
+        s++;
+        n = -n;
+    }
+    if (n < 1024) {
+        /* Bytes */
+        sprintf(s,"%lluB",n);
+        return;
+    } else if (n < (1024*1024)) {
+        d = (double)n/(1024);
+        sprintf(s,"%.2fK",d);
+    } else if (n < (1024LL*1024*1024)) {
+        d = (double)n/(1024*1024);
+        sprintf(s,"%.2fM",d);
+    } else if (n < (1024LL*1024*1024*1024)) {
+        d = (double)n/(1024LL*1024*1024);
+        sprintf(s,"%.2fG",d);
+    }
+}
+
+static void statMode() {
+    redisReply *reply;
+    long aux, requests = 0;
+    int i = 0;
+
+    while(1) {
+        char buf[64];
+        int j;
+
+        reply = reconnectingInfo();
+        if (reply->type == REDIS_REPLY_ERROR) {
+            printf("ERROR: %s\n", reply->str);
+            exit(1);
+        }
+
+        if ((i++ % 20) == 0) {
+            printf(
+"------- data ------ --------------------- load -------------------- - child -\n"
+"keys       mem      clients blocked requests            connections          \n");
+        }
+
+        /* Keys */
+        aux = 0;
+        for (j = 0; j < 20; j++) {
+            long k;
+
+            sprintf(buf,"db%d:keys",j);
+            k = getLongInfoField(reply->str,buf);
+            if (k == LONG_MIN) continue;
+            aux += k;
+        }
+        sprintf(buf,"%ld",aux);
+        printf("%-11s",buf);
+
+        /* Used memory */
+        aux = getLongInfoField(reply->str,"used_memory");
+        bytesToHuman(buf,aux);
+        printf("%-8s",buf);
+
+        /* Clients */
+        aux = getLongInfoField(reply->str,"connected_clients");
+        sprintf(buf,"%ld",aux);
+        printf(" %-8s",buf);
+
+        /* Blocked (BLPOPPING) Clients */
+        aux = getLongInfoField(reply->str,"blocked_clients");
+        sprintf(buf,"%ld",aux);
+        printf("%-8s",buf);
+
+        /* Requets */
+        aux = getLongInfoField(reply->str,"total_commands_processed");
+        sprintf(buf,"%ld (+%ld)",aux,requests == 0 ? 0 : aux-requests);
+        printf("%-19s",buf);
+        requests = aux;
+
+        /* Connections */
+        aux = getLongInfoField(reply->str,"total_connections_received");
+        sprintf(buf,"%ld",aux);
+        printf(" %-12s",buf);
+
+        /* Children */
+        aux = getLongInfoField(reply->str,"bgsave_in_progress");
+        aux |= getLongInfoField(reply->str,"aof_rewrite_in_progress") << 1;
+        switch(aux) {
+        case 0: break;
+        case 1:
+            printf("SAVE");
+            break;
+        case 2:
+            printf("AOF");
+            break;
+        case 3:
+            printf("SAVE+AOF");
+            break;
+        }
+
+        printf("\n");
+        freeReplyObject(reply);
+        usleep(config.interval);
+    }
+}
+
 int main(int argc, char **argv) {
     int firstarg;
 
@@ -1330,6 +1503,13 @@ int main(int argc, char **argv) {
         findBigKeys();
     }
 
+    /* Stat mode */
+    if (config.stat_mode) {
+        if (cliConnect(0) == REDIS_ERR) exit(1);
+        if (config.interval == 0) config.interval = 1000000;
+        statMode();
+    }
+
     /* Start interactive mode when no command is provided */
     if (argc == 0 && !config.eval) {
         /* Note that in repl mode we don't abort on connection error.