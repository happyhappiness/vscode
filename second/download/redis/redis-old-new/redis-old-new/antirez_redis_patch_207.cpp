@@ -1048,8 +1048,8 @@ struct redisServer {
     long long latency_monitor_threshold;
     dict *latency_events;
     /* Assert & bug reporting */
-    char *assert_failed;
-    char *assert_file;
+    const char *assert_failed;
+    const char *assert_file;
     int assert_line;
     int bug_report_start; /* True if bug report header was already logged. */
     int watchdog_period;  /* Software watchdog period in ms. 0 = off */
@@ -1245,7 +1245,7 @@ void addReplyStatusFormat(client *c, const char *fmt, ...);
 void listTypeTryConversion(robj *subject, robj *value);
 void listTypePush(robj *subject, robj *value, int where);
 robj *listTypePop(robj *subject, int where);
-unsigned long listTypeLength(robj *subject);
+unsigned long listTypeLength(const robj *subject);
 listTypeIterator *listTypeInitIterator(robj *subject, long index, unsigned char direction);
 void listTypeReleaseIterator(listTypeIterator *li);
 int listTypeNext(listTypeIterator *li, listTypeEntry *entry);
@@ -1305,7 +1305,7 @@ int getLongFromObjectOrReply(client *c, robj *o, long *target, const char *msg);
 int checkType(client *c, robj *o, int type);
 int getLongLongFromObjectOrReply(client *c, robj *o, long long *target, const char *msg);
 int getDoubleFromObjectOrReply(client *c, robj *o, double *target, const char *msg);
-int getDoubleFromObject(robj *o, double *target);
+int getDoubleFromObject(const robj *o, double *target);
 int getLongLongFromObject(robj *o, long long *target);
 int getLongDoubleFromObject(robj *o, long double *target);
 int getLongDoubleFromObjectOrReply(client *c, robj *o, long double *target, const char *msg);
@@ -1406,7 +1406,7 @@ void zzlNext(unsigned char *zl, unsigned char **eptr, unsigned char **sptr);
 void zzlPrev(unsigned char *zl, unsigned char **eptr, unsigned char **sptr);
 unsigned char *zzlFirstInRange(unsigned char *zl, zrangespec *range);
 unsigned char *zzlLastInRange(unsigned char *zl, zrangespec *range);
-unsigned int zsetLength(robj *zobj);
+unsigned int zsetLength(const robj *zobj);
 void zsetConvert(robj *zobj, int encoding);
 void zsetConvertToZiplistIfNeeded(robj *zobj, size_t maxelelen);
 int zsetScore(robj *zobj, sds member, double *score);
@@ -1479,7 +1479,7 @@ int setTypeNext(setTypeIterator *si, sds *sdsele, int64_t *llele);
 sds setTypeNextObject(setTypeIterator *si);
 int setTypeRandomElement(robj *setobj, sds *sdsele, int64_t *llele);
 unsigned long setTypeRandomElements(robj *set, unsigned long count, robj *aux_set);
-unsigned long setTypeSize(robj *subject);
+unsigned long setTypeSize(const robj *subject);
 void setTypeConvert(robj *subject, int enc);
 
 /* Hash data type */
@@ -1492,7 +1492,7 @@ void hashTypeTryConversion(robj *subject, robj **argv, int start, int end);
 void hashTypeTryObjectEncoding(robj *subject, robj **o1, robj **o2);
 int hashTypeExists(robj *o, sds key);
 int hashTypeDelete(robj *o, sds key);
-unsigned long hashTypeLength(robj *o);
+unsigned long hashTypeLength(const robj *o);
 hashTypeIterator *hashTypeInitIterator(robj *subject);
 void hashTypeReleaseIterator(hashTypeIterator *hi);
 int hashTypeNext(hashTypeIterator *hi);
@@ -1799,11 +1799,11 @@ void *realloc(void *ptr, size_t size) __attribute__ ((deprecated));
 #endif
 
 /* Debugging stuff */
-void _serverAssertWithInfo(client *c, robj *o, char *estr, char *file, int line);
-void _serverAssert(char *estr, char *file, int line);
-void _serverPanic(char *msg, char *file, int line);
+void _serverAssertWithInfo(const client *c, const robj *o, const char *estr, const char *file, int line);
+void _serverAssert(const char *estr, const char *file, int line);
+void _serverPanic(const char *msg, const char *file, int line);
 void bugReportStart(void);
-void serverLogObjectDebugInfo(robj *o);
+void serverLogObjectDebugInfo(const robj *o);
 void sigsegvHandler(int sig, siginfo_t *info, void *secret);
 sds genRedisInfoString(char *section);
 void enableWatchdog(int period);