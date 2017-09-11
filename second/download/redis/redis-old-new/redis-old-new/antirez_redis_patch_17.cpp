@@ -546,6 +546,22 @@ typedef struct RedisModuleIO {
     iovar.ctx = NULL; \
 } while(0);
 
+/* This is a structure used to export DEBUG DIGEST capabilities to Redis
+ * modules. We want to capture both the ordered and unordered elements of
+ * a data structure, so that a digest can be created in a way that correctly
+ * reflects the values. See the DEBUG DIGEST command implementation for more
+ * background. */
+typedef struct RedisModuleDigest {
+    unsigned char o[20];    /* Ordered elements. */
+    unsigned char x[20];    /* Xored elements. */
+} RedisModuleDigest;
+
+/* Just start with a digest composed of all zero bytes. */
+#define moduleInitDigestContext(mdvar) do { \
+    memset(mdvar.o,0,sizeof(mdvar.o)); \
+    memset(mdvar.x,0,sizeof(mdvar.x)); \
+} while(0);
+
 /* Objects encoding. Some kind of objects like Strings and Hashes can be
  * internally represented in multiple ways. The 'encoding' field of the object
  * is set to one of this fields for this object. */
@@ -1993,6 +2009,8 @@ void disableWatchdog(void);
 void watchdogScheduleSignal(int period);
 void serverLogHexDump(int level, char *descr, void *value, size_t len);
 int memtest_preserving_test(unsigned long *m, size_t bytes, int passes);
+void mixDigest(unsigned char *digest, void *ptr, size_t len);
+void xorDigest(unsigned char *digest, void *ptr, size_t len);
 
 #define redisDebug(fmt, ...) \
     printf("DEBUG %s:%d > " fmt "\n", __FILE__, __LINE__, __VA_ARGS__)