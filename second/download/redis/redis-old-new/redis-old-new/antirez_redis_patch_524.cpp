@@ -35,39 +35,169 @@
 
 #include <sys/types.h>
 #include <stdarg.h>
+#include <stdint.h>
 
 typedef char *sds;
 
-struct sdshdr {
-    unsigned int len;
-    unsigned int free;
+struct __attribute__ ((__packed__)) sdshdr8 {
+    uint8_t len; /* used */
+    uint8_t alloc; /* excluding the header and null terminator */
+    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    char buf[];
+};
+struct __attribute__ ((__packed__)) sdshdr16 {
+    uint16_t len; /* used */
+    uint16_t alloc; /* excluding the header and null terminator */
+    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    char buf[];
+};
+struct __attribute__ ((__packed__)) sdshdr32 {
+    uint32_t len; /* used */
+    uint32_t alloc; /* excluding the header and null terminator */
+    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    char buf[];
+};
+struct __attribute__ ((__packed__)) sdshdr64 {
+    uint64_t len; /* used */
+    uint64_t alloc; /* excluding the header and null terminator */
+    char flags; /* 2 lsb of type, and 6 msb of refcount */
     char buf[];
 };
 
+#define SDS_TYPE_8  0
+#define SDS_TYPE_16 1
+#define SDS_TYPE_32 2
+#define SDS_TYPE_64 3
+#define SDS_TYPE_MASK 3
+#define SDS_TYPE_BITS 2
+#define SDS_HDR_VAR(T,s) struct sdshdr##T *sh = (void*)((s)-(sizeof(struct sdshdr##T)));
+#define SDS_HDR(T,s) ((struct sdshdr##T *)((s)-(sizeof(struct sdshdr##T))))
+
 static inline size_t sdslen(const sds s) {
-    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
-    return sh->len;
+    char flags = s[-1];
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_8:
+            return SDS_HDR(8,s)->len;
+        case SDS_TYPE_16:
+            return SDS_HDR(16,s)->len;
+        case SDS_TYPE_32:
+            return SDS_HDR(32,s)->len;
+        case SDS_TYPE_64:
+            return SDS_HDR(64,s)->len;
+    }
+    return 0;
 }
 
 static inline size_t sdsavail(const sds s) {
-    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
-    return sh->free;
+    char flags = s[-1];
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_8: {
+            SDS_HDR_VAR(8,s);
+            return sh->alloc - sh->len;
+        }
+        case SDS_TYPE_16: {
+            SDS_HDR_VAR(16,s);
+            return sh->alloc - sh->len;
+        }
+        case SDS_TYPE_32: {
+            SDS_HDR_VAR(32,s);
+            return sh->alloc - sh->len;
+        }
+        case SDS_TYPE_64: {
+            SDS_HDR_VAR(64,s);
+            return sh->alloc - sh->len;
+        }
+    }
+    return 0;
+}
+
+static inline void sdssetlen(sds s, size_t newlen) {
+    char flags = s[-1];
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_8:
+            SDS_HDR(8,s)->len = newlen;
+            break;
+        case SDS_TYPE_16:
+            SDS_HDR(16,s)->len = newlen;
+            break;
+        case SDS_TYPE_32:
+            SDS_HDR(32,s)->len = newlen;
+            break;
+        case SDS_TYPE_64:
+            SDS_HDR(64,s)->len = newlen;
+            break;
+    }
+}
+
+static inline void sdsinclen(sds s, size_t inc) {
+    char flags = s[-1];
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_8:
+            SDS_HDR(8,s)->len += inc;
+            break;
+        case SDS_TYPE_16:
+            SDS_HDR(16,s)->len += inc;
+            break;
+        case SDS_TYPE_32:
+            SDS_HDR(32,s)->len += inc;
+            break;
+        case SDS_TYPE_64:
+            SDS_HDR(64,s)->len += inc;
+            break;
+    }
+}
+
+/* sdsalloc() = sdsavail() + sdslen() */
+static inline size_t sdsalloc(const sds s) {
+    char flags = s[-1];
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_8:
+            return SDS_HDR(8,s)->alloc;
+        case SDS_TYPE_16:
+            return SDS_HDR(16,s)->alloc;
+        case SDS_TYPE_32:
+            return SDS_HDR(32,s)->alloc;
+        case SDS_TYPE_64:
+            return SDS_HDR(64,s)->alloc;
+    }
+    return 0;
+}
+
+static inline void sdssetalloc(sds s, size_t newlen) {
+    char flags = s[-1];
+    switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_8:
+            SDS_HDR(8,s)->alloc = newlen;
+            break;
+        case SDS_TYPE_16:
+            SDS_HDR(16,s)->alloc = newlen;
+            break;
+        case SDS_TYPE_32:
+            SDS_HDR(32,s)->alloc = newlen;
+            break;
+        case SDS_TYPE_64:
+            SDS_HDR(64,s)->alloc = newlen;
+            break;
+    }
 }
 
 sds sdsnewlen(const void *init, size_t initlen);
 sds sdsnew(const char *init);
 sds sdsempty(void);
-size_t sdslen(const sds s);
 sds sdsdup(const sds s);
 void sdsfree(sds s);
-size_t sdsavail(const sds s);
 sds sdsgrowzero(sds s, size_t len);
 sds sdscatlen(sds s, const void *t, size_t len);
 sds sdscat(sds s, const char *t);
 sds sdscatsds(sds s, const sds t);
 sds sdscpylen(sds s, const char *t, size_t len);
 sds sdscpy(sds s, const char *t);
 
+/* we can add a reference count on top of any 
+ * existing sds. (max up to 63 references) */
+void sdsIncRefcount(sds s);
+void sdsDecRefcount(sds s);
+
 sds sdscatvprintf(sds s, const char *fmt, va_list ap);
 #ifdef __GNUC__
 sds sdscatprintf(sds s, const char *fmt, ...)
@@ -97,6 +227,7 @@ sds sdsMakeRoomFor(sds s, size_t addlen);
 void sdsIncrLen(sds s, int incr);
 sds sdsRemoveFreeSpace(sds s);
 size_t sdsAllocSize(sds s);
+size_t sdsZmallocSize(sds s);
 
 #ifdef REDIS_TEST
 int sdsTest(int argc, char *argv[]);