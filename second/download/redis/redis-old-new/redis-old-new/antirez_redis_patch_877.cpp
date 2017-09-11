@@ -39,6 +39,7 @@
 #include <unistd.h>
 #include <sys/socket.h>
 #include <sys/stat.h>
+#include <sys/file.h>
 
 /* A global reference to myself is handy to make code more clear.
  * Myself always points to server.cluster->myself, that is, the clusterNode
@@ -90,13 +91,27 @@ uint64_t clusterGetMaxEpoch(void) {
     return max;
 }
 
+/* Load the cluster config from 'filename'.
+ *
+ * If the file does not exist or is zero-length (this may happen because
+ * when we lock the nodes.conf file, we create a zero-length one for the
+ * sake of locking if it does not already exist), REDIS_ERR is returned.
+ * If the configuration was loaded from the file, REDIS_OK is returned. */
 int clusterLoadConfig(char *filename) {
     FILE *fp = fopen(filename,"r");
+    struct stat sb;
     char *line;
     int maxline, j;
    
     if (fp == NULL) return REDIS_ERR;
 
+    /* Check if the file is zero-length: if so return REDIS_ERR to signal
+     * we have to write the config. */
+    if (fstat(fileno(fp),&sb) != -1 && sb.st_size == 0) {
+        fclose(fp);
+        return REDIS_ERR;
+    }
+
     /* Parse the file. Note that single liens of the cluster config file can
      * be really long as they include all the hash slots of the node.
      * This means in the worst possible case, half of the Redis slots will be
@@ -323,6 +338,46 @@ void clusterSaveConfigOrDie(int do_fsync) {
     }
 }
 
+/* Lock the cluster config using flock(), and leaks the file descritor used to
+ * acquire the lock so that the file will be locked forever.
+ *
+ * This works because we always update nodes.conf with a new version
+ * in-place, reopening the file, and writing to it in place (later adjusting
+ * the length with ftruncate()).
+ *
+ * On success REDIS_OK is returned, otherwise an error is logged and
+ * the function returns REDIS_ERR to signal a lock was not acquired. */
+int clusterLockConfig(char *filename) {
+    /* To lock it, we need to open the file in a way it is created if
+     * it does not exist, otherwise there is a race condition with other
+     * processes. */
+    int fd = open(filename,O_WRONLY|O_CREAT,0644);
+    if (fd == -1) {
+        redisLog(REDIS_WARNING,
+            "Can't open %s in order to acquire a lock: %s",
+            filename, strerror(errno));
+        return REDIS_ERR;
+    }
+
+    if (flock(fd,LOCK_EX|LOCK_NB) == -1) {
+        if (errno == EWOULDBLOCK) {
+            redisLog(REDIS_WARNING,
+                 "Sorry, the cluster configuration file %s is already used "
+                 "by a different Redis Cluster node. Please make sure that "
+                 "different nodes use different cluster configuration "
+                 "files.", filename);
+        } else {
+            redisLog(REDIS_WARNING,
+                "Impossible to lock %s: %s", filename, strerror(errno));
+        }
+        close(fd);
+        return REDIS_ERR;
+    }
+    /* Lock acquired: leak the 'fd' by not closing it, so that we'll retain the
+     * lock to the file as long as the process exists. */
+    return REDIS_OK;
+}
+
 void clusterInit(void) {
     int saveconf = 0;
 
@@ -344,6 +399,13 @@ void clusterInit(void) {
     server.cluster->stats_bus_messages_received = 0;
     memset(server.cluster->slots,0, sizeof(server.cluster->slots));
     clusterCloseAllSlots();
+
+    /* Lock the cluster config file to make sure every node uses
+     * its own nodes.conf. */
+    if (clusterLockConfig(server.cluster_configfile) == REDIS_ERR)
+        exit(1);
+
+    /* Load or create a new nodes configuration. */
     if (clusterLoadConfig(server.cluster_configfile) == REDIS_ERR) {
         /* No configuration found. We will just use the random name provided
          * by the createClusterNode() function. */