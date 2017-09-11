@@ -41,6 +41,7 @@
 #include <sys/stat.h>
 #include <sys/time.h>
 #include <assert.h>
+#include <fcntl.h>
 
 #include "hiredis.h"
 #include "sds.h"
@@ -73,6 +74,8 @@ static struct config {
     int cluster_reissue_command;
     int slave_mode;
     int pipe_mode;
+    int getrdb_mode;
+    char *rdb_filename;
     int bigkeys;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
@@ -660,6 +663,9 @@ static int parseOptions(int argc, char **argv) {
             config.latency_mode = 1;
         } else if (!strcmp(argv[i],"--slave")) {
             config.slave_mode = 1;
+        } else if (!strcmp(argv[i],"--rdb") && !lastarg) {
+            config.getrdb_mode = 1;
+            config.rdb_filename = argv[++i];
         } else if (!strcmp(argv[i],"--pipe")) {
             config.pipe_mode = 1;
         } else if (!strcmp(argv[i],"--bigkeys")) {
@@ -720,6 +726,7 @@ static void usage() {
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency\n"
 "  --slave          Simulate a slave showing commands received from the master\n"
+"  --rdb <filename> Transfer an RDB dump from remote server to local file.\n"
 "  --pipe           Transfer raw Redis protocol from stdin to server\n"
 "  --bigkeys        Sample Redis keys looking for big keys\n"
 "  --eval <file>    Send an EVAL command using the Lua script at <file>\n"
@@ -927,15 +934,15 @@ static void latencyMode(void) {
     }
 }
 
-static void slaveMode(void) {
+/* Sends SYNC and reads the number of bytes in the payload. Used both by
+ * slaveMode() and getRDB(). */
+unsigned long long sendSync(int fd) {
     /* To start we need to send the SYNC command and return the payload.
      * The hiredis client lib does not understand this part of the protocol
      * and we don't want to mess with its buffers, so everything is performed
      * using direct low-level I/O. */
-    int fd = context->fd;
-    char buf[1024], *p;
+    char buf[4096], *p;
     ssize_t nread;
-    unsigned long long payload;
 
     /* Send the SYNC command. */
     if (write(fd,"SYNC\r\n",6) != 6) {
@@ -955,12 +962,25 @@ static void slaveMode(void) {
         p++;
     }
     *p = '\0';
-    payload = strtoull(buf+1,NULL,10);
-    fprintf(stderr,"SYNC with master, discarding %lld bytes of bulk tranfer...\n",
-            payload);
+    if (buf[0] == '-') {
+        printf("SYNC with master failed: %s\n", buf);
+        exit(1);
+    }
+    return strtoull(buf+1,NULL,10);
+}
+
+static void slaveMode(void) {
+    int fd = context->fd;
+    unsigned long long payload = sendSync(fd);
+    char buf[1024];
+
+    fprintf(stderr,"SYNC with master, discarding %llu "
+                   "bytes of bulk tranfer...\n", payload);
 
     /* Discard the payload. */
     while(payload) {
+        ssize_t nread;
+
         nread = read(fd,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
         if (nread <= 0) {
             fprintf(stderr,"Error reading RDB payload while SYNCing\n");
@@ -970,11 +990,56 @@ static void slaveMode(void) {
     }
     fprintf(stderr,"SYNC done. Logging commands from master.\n");
 
-    /* Now we can use the hiredis to read the incoming protocol. */
+    /* Now we can use hiredis to read the incoming protocol. */
     config.output = OUTPUT_CSV;
     while (cliReadReply(0) == REDIS_OK);
 }
 
+/* This function implements --rdb, so it uses the replication protocol in order
+ * to fetch the RDB file from a remote server. */
+static void getRDB(void) {
+    int s = context->fd;
+    int fd;
+    unsigned long long payload = sendSync(s);
+    char buf[4096];
+
+    fprintf(stderr,"SYNC sent to master, writing %llu bytes to '%s'\n",
+        payload, config.rdb_filename);
+
+    /* Write to file. */
+    if (!strcmp(config.rdb_filename,"-")) {
+        fd = STDOUT_FILENO;
+    } else {
+        fd = open(config.rdb_filename, O_CREAT|O_WRONLY, 0644);
+        if (fd == -1) {
+            fprintf(stderr, "Error opening '%s': %s\n", config.rdb_filename,
+                strerror(errno));
+            exit(1);
+        }
+    }
+
+    while(payload) {
+        ssize_t nread, nwritten;
+        
+        nread = read(s,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
+        if (nread <= 0) {
+            fprintf(stderr,"I/O Error reading RDB payload from socket\n");
+            exit(1);
+        }
+        nwritten = write(fd, buf, nread);
+        if (nwritten != nread) {
+            fprintf(stderr,"Error writing data to file: %s\n",
+                strerror(errno));
+            exit(1);
+        }
+        payload -= nread;
+    }
+    close(s); /* Close the file descriptor ASAP as fsync() may take time. */
+    fsync(fd);
+    fprintf(stderr,"Transfer finished with success.\n");
+    exit(0);
+}
+
 static void pipeMode(void) {
     int fd = context->fd;
     long long errors = 0, replies = 0, obuf_len = 0, obuf_pos = 0;
@@ -1203,6 +1268,8 @@ int main(int argc, char **argv) {
     config.latency_mode = 0;
     config.cluster_mode = 0;
     config.slave_mode = 0;
+    config.getrdb_mode = 0;
+    config.rdb_filename = NULL;
     config.pipe_mode = 0;
     config.bigkeys = 0;
     config.stdinarg = 0;
@@ -1231,6 +1298,12 @@ int main(int argc, char **argv) {
         slaveMode();
     }
 
+    /* Get RDB mode. */
+    if (config.getrdb_mode) {
+        cliConnect(0);
+        getRDB();
+    }
+
     /* Pipe mode */
     if (config.pipe_mode) {
         if (cliConnect(0) == REDIS_ERR) exit(1);