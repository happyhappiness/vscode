@@ -46,6 +46,8 @@
 #include "zmalloc.h"
 #include "linenoise.h"
 #include "help.h"
+#include "anet.h"
+#include "ae.h"
 
 #define REDIS_NOTUSED(V) ((void) V)
 
@@ -69,6 +71,7 @@ static struct config {
     int cluster_mode;
     int cluster_reissue_command;
     int slave_mode;
+    int pipe_mode;
     int bigkeys;
     int stdinarg; /* get last arg from stdin. (-x option) */
     char *auth;
@@ -656,6 +659,8 @@ static int parseOptions(int argc, char **argv) {
             config.latency_mode = 1;
         } else if (!strcmp(argv[i],"--slave")) {
             config.slave_mode = 1;
+        } else if (!strcmp(argv[i],"--pipe")) {
+            config.pipe_mode = 1;
         } else if (!strcmp(argv[i],"--bigkeys")) {
             config.bigkeys = 1;
         } else if (!strcmp(argv[i],"--eval") && !lastarg) {
@@ -714,6 +719,7 @@ static void usage() {
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --latency        Enter a special mode continuously sampling latency.\n"
 "  --slave          Simulate a slave showing commands received from the master.\n"
+"  --pipe           Transfer raw Redis protocol from stdin to server.\n"
 "  --bigkeys        Sample Redis keys looking for big keys.\n"
 "  --eval <file>    Send an EVAL command using the Lua script at <file>.\n"
 "  --help           Output this help and exit\n"
@@ -968,6 +974,133 @@ static void slaveMode(void) {
     while (cliReadReply(0) == REDIS_OK);
 }
 
+static void pipeMode(void) {
+    int fd = context->fd;
+    long long errors = 0, replies = 0, obuf_len = 0, obuf_pos = 0;
+    char ibuf[1024*16], obuf[1024*16]; /* Input and output buffers */
+    char aneterr[ANET_ERR_LEN];
+    redisReader *reader = redisReaderCreate();
+    redisReply *reply;
+    int eof = 0; /* True once we consumed all the standard input. */
+    int done = 0;
+    char magic[20]; /* Special reply we recognize. */
+
+    srand(time(NULL));
+
+    /* Use non blocking I/O. */
+    if (anetNonBlock(aneterr,fd) == ANET_ERR) {
+        fprintf(stderr, "Can't set the socket in non blocking mode: %s\n",
+            aneterr);
+        exit(1);
+    }
+
+    /* Transfer raw protocol and read replies from the server at the same
+     * time. */
+    while(!done) {
+        int mask = AE_READABLE;
+
+        if (!eof || obuf_len != 0) mask |= AE_WRITABLE;
+        mask = aeWait(fd,mask,1000);
+
+        /* Handle the readable state: we can read replies from the server. */
+        if (mask & AE_READABLE) {
+            ssize_t nread;
+
+            /* Read from socket and feed the hiredis reader. */
+            do {
+                nread = read(fd,ibuf,sizeof(ibuf));
+                if (nread == -1 && errno != EAGAIN) {
+                    fprintf(stderr, "Error reading from the server: %s\n",
+                        strerror(errno));
+                    exit(1);
+                }
+                if (nread > 0) redisReaderFeed(reader,ibuf,nread);
+            } while(nread > 0);
+
+            /* Consume replies. */
+            do {
+                if (redisReaderGetReply(reader,(void**)&reply) == REDIS_ERR) {
+                    fprintf(stderr, "Error reading replies from server\n");
+                    exit(1);
+                }
+                if (reply) {
+                    if (reply->type == REDIS_REPLY_ERROR) {
+                        fprintf(stderr,"%s\n", reply->str);
+                        errors++;
+                    } else if (eof && reply->type == REDIS_REPLY_STRING &&
+                                      reply->len == 20) {
+                        /* Check if this is the reply to our final ECHO 
+                         * command. If so everything was received
+                         * from the server. */
+                        if (memcmp(reply->str,magic,20) == 0) {
+                            printf("Last reply received from server.\n");
+                            done = 1;
+                            replies--;
+                        }
+                    }
+                    replies++;
+                    freeReplyObject(reply);
+                }
+            } while(reply);
+        }
+
+        /* Handle the writable state: we can send protocol to the server. */
+        if (mask & AE_WRITABLE) {
+            while(1) {
+                /* Transfer current buffer to server. */
+                if (obuf_len != 0) {
+                    ssize_t nwritten = write(fd,obuf+obuf_pos,obuf_len);
+                    
+                    if (nwritten == -1) {
+                        fprintf(stderr, "Error writing to the server: %s\n",
+                            strerror(errno));
+                        exit(1);
+                    }
+                    obuf_len -= nwritten;
+                    obuf_pos += nwritten;
+                    if (obuf_len != 0) break; /* Can't accept more data. */
+                }
+                /* If buffer is empty, load from stdin. */
+                if (obuf_len == 0 && !eof) {
+                    ssize_t nread = read(STDIN_FILENO,obuf,sizeof(obuf));
+
+                    if (nread == 0) {
+                        char echo[] =
+                        "*2\r\n$4\r\nECHO\r\n$20\r\n01234567890123456789\r\n";
+                        int j;
+
+                        eof = 1;
+                        /* Everything transfered, so we queue a special
+                         * ECHO command that we can match in the replies
+                         * to make sure everything was read from the server. */
+                        for (j = 0; j < 20; j++)
+                            magic[j] = rand() & 0xff;
+                        memcpy(echo+19,magic,20);
+                        memcpy(obuf,echo,sizeof(echo)-1);
+                        obuf_len = sizeof(echo)-1;
+                        obuf_pos = 0;
+                        printf("All data transferred. Waiting for the last reply...\n");
+                    } else if (nread == -1) {
+                        fprintf(stderr, "Error reading from stdin: %s\n",
+                            strerror(errno));
+                        exit(1);
+                    } else {
+                        obuf_len = nread;
+                        obuf_pos = 0;
+                    }
+                }
+                if (obuf_len == 0 && eof) break;
+            }
+        }
+    }
+    redisReaderFree(reader);
+    printf("errors: %lld, replies: %lld\n", errors, replies);
+    if (errors)
+        exit(1);
+    else
+        exit(0);
+}
+
 #define TYPE_STRING 0
 #define TYPE_LIST   1
 #define TYPE_SET    2
@@ -1065,6 +1198,7 @@ int main(int argc, char **argv) {
     config.latency_mode = 0;
     config.cluster_mode = 0;
     config.slave_mode = 0;
+    config.pipe_mode = 0;
     config.bigkeys = 0;
     config.stdinarg = 0;
     config.auth = NULL;
@@ -1080,18 +1214,24 @@ int main(int argc, char **argv) {
     argc -= firstarg;
     argv += firstarg;
 
-    /* Start in latency mode if appropriate */
+    /* Latency mode */
     if (config.latency_mode) {
         cliConnect(0);
         latencyMode();
     }
 
-    /* Start in slave mode if appropriate */
+    /* Slave mode */
     if (config.slave_mode) {
         cliConnect(0);
         slaveMode();
     }
 
+    /* Pipe mode */
+    if (config.pipe_mode) {
+        cliConnect(0);
+        pipeMode();
+    }
+
     /* Find big keys */
     if (config.bigkeys) {
         cliConnect(0);