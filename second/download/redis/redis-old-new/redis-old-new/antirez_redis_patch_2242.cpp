@@ -152,6 +152,12 @@
 #define REDIS_RDB_ENC_INT32 2       /* 32 bit signed integer */
 #define REDIS_RDB_ENC_LZF 3         /* string compressed with FASTLZ */
 
+/* Virtual memory object->where field. */
+#define REDIS_VM_MEMORY 0       /* The object is on memory */
+#define REDIS_VM_SWAPPED 1      /* The object is on disk */
+#define REDIS_VM_SWAPPING 2     /* Redis is swapping this object on disk */
+#define REDIS_VM_LOADING 3      /* Redis is loading this object from disk */
+
 /* Client flags */
 #define REDIS_CLOSE 1       /* This client connection should be closed ASAP */
 #define REDIS_SLAVE 2       /* This client is a slave server */
@@ -207,12 +213,26 @@ static void _redisAssert(char *estr);
 /*================================= Data types ============================== */
 
 /* A redis object, that is a type able to hold a string / list / set */
+
+/* The VM object structure */
+struct redisObjectVM {
+    off_t offset;   /* the page at witch the object is stored on disk */
+    int pages;   /* number of pages used on disk */
+} vm;
+
+/* The actual Redis Object */
 typedef struct redisObject {
     void *ptr;
     unsigned char type;
     unsigned char encoding;
-    unsigned char notused[2];
+    unsigned char storage;  /* where? REDIS_VM_MEMORY, REDIS_VM_SWAPPED, ... */
+    unsigned char notused;
     int refcount;
+    /* VM fields, this are only allocated if VM is active, otherwise the
+     * object allocation function will just allocate
+     * sizeof(redisObjct) minus sizeof(redisObjectVM), so using
+     * Redis without VM active will not have any overhead. */
+    struct redisObjectVM vm;
 } robj;
 
 /* Macro used to initalize a Redis object allocated on the stack.
@@ -339,6 +359,16 @@ struct redisServer {
     int sort_desc;
     int sort_alpha;
     int sort_bypattern;
+    /* Virtual memory configuration */
+    int vm_enabled;
+    off_t vm_page_size;
+    off_t vm_pages;
+    long vm_max_memory;
+    /* Virtual memory state */
+    FILE *vm_fp;
+    int vm_fd;
+    off_t vm_next_page; /* Next probably empty page */
+    off_t vm_near_pages; /* Number of pages allocated sequentially */
 };
 
 typedef void redisCommandProc(redisClient *c);
@@ -447,6 +477,7 @@ static void freeClientMultiState(redisClient *c);
 static void queueMultiCommand(redisClient *c, struct redisCommand *cmd);
 static void unblockClient(redisClient *c);
 static int handleClientsWaitingListPush(redisClient *c, robj *key, robj *ele);
+static void vmInit(void);
 
 static void authCommand(redisClient *c);
 static void pingCommand(redisClient *c);
@@ -1207,6 +1238,11 @@ static void initServerConfig() {
     server.maxclients = 0;
     server.blockedclients = 0;
     server.maxmemory = 0;
+    server.vm_enabled = 0;
+    server.vm_page_size = 256;          /* 256 bytes per page */
+    server.vm_pages = 1024*1024*100;    /* 104 millions of pages */
+    server.vm_max_memory = 1024LL*1024*1024*1; /* 1 GB of RAM */
+
     resetServerSaveParams();
 
     appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
@@ -1273,6 +1309,8 @@ static void initServer() {
             exit(1);
         }
     }
+
+    if (server.vm_enabled) vmInit();
 }
 
 /* Empty the whole database */
@@ -1439,6 +1477,10 @@ static void loadServerConfig(char *filename) {
           server.pidfile = zstrdup(argv[1]);
         } else if (!strcasecmp(argv[0],"dbfilename") && argc == 2) {
           server.dbfilename = zstrdup(argv[1]);
+        } else if (!strcasecmp(argv[0],"vm-enabled") && argc == 2) {
+            if ((server.vm_enabled = yesnotoi(argv[1])) == -1) {
+                err = "argument must be 'yes' or 'no'"; goto loaderr;
+            }
         } else {
             err = "Bad directive or wrong number of arguments"; goto loaderr;
         }
@@ -2194,7 +2236,11 @@ static robj *createObject(int type, void *ptr) {
         o = listNodeValue(head);
         listDelNode(server.objfreelist,head);
     } else {
-        o = zmalloc(sizeof(*o));
+        if (server.vm_enabled) {
+            o = zmalloc(sizeof(*o));
+        } else {
+            o = zmalloc(sizeof(*o)-sizeof(struct redisObjectVM));
+        }
     }
     o->type = type;
     o->encoding = REDIS_ENCODING_RAW;
@@ -6532,6 +6578,32 @@ static void aofRemoveTempFile(pid_t childpid) {
     unlink(tmpfile);
 }
 
+/* =============================== Virtual Memory =========================== */
+static void vmInit(void) {
+    off_t totsize;
+
+    server.vm_fp = fopen("/tmp/redisvm","w+b");
+    if (server.vm_fp == NULL) {
+        redisLog(REDIS_WARNING,"Impossible to open the swap file. Exiting.");
+        exit(1);
+    }
+    server.vm_fd = fileno(server.vm_fp);
+    server.vm_next_page = 0;
+    server.vm_near_pages = 0;
+    totsize = server.vm_pages*server.vm_page_size;
+    redisLog(REDIS_NOTICE,"Allocating %lld bytes of swap file",totsize);
+    if (ftruncate(server.vm_fd,totsize) == -1) {
+        redisLog(REDIS_WARNING,"Can't ftruncate swap file: %s. Exiting.",
+            strerror(errno));
+        exit(1);
+    } else {
+        redisLog(REDIS_NOTICE,"Swap file allocated with success");
+    }
+    /* Try to remove the swap file, so the OS will really delete it from the
+     * file system when Redis exists. */
+    unlink("/tmp/redisvm");
+}
+
 /* ================================= Debugging ============================== */
 
 static void debugCommand(redisClient *c) {