@@ -39,43 +39,53 @@
 
 typedef char *sds;
 
+/* Note: sdshdr5 is never used, we just access the flags byte directly.
+ * However is here to document the layout of type 5 SDS strings. */
+struct __attribute__ ((__packed__)) sdshdr5 {
+    unsigned char flags; /* 3 lsb of type, and 5 msb of string length */
+    char buf[];
+};
 struct __attribute__ ((__packed__)) sdshdr8 {
     uint8_t len; /* used */
     uint8_t alloc; /* excluding the header and null terminator */
-    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    unsigned char flags; /* 3 lsb of type, 5 unused bits */
     char buf[];
 };
 struct __attribute__ ((__packed__)) sdshdr16 {
     uint16_t len; /* used */
     uint16_t alloc; /* excluding the header and null terminator */
-    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    unsigned char flags; /* 3 lsb of type, 5 unused bits */
     char buf[];
 };
 struct __attribute__ ((__packed__)) sdshdr32 {
     uint32_t len; /* used */
     uint32_t alloc; /* excluding the header and null terminator */
-    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    unsigned char flags; /* 3 lsb of type, 5 unused bits */
     char buf[];
 };
 struct __attribute__ ((__packed__)) sdshdr64 {
     uint64_t len; /* used */
     uint64_t alloc; /* excluding the header and null terminator */
-    char flags; /* 2 lsb of type, and 6 msb of refcount */
+    unsigned char flags; /* 3 lsb of type, 5 unused bits */
     char buf[];
 };
 
-#define SDS_TYPE_8  0
-#define SDS_TYPE_16 1
-#define SDS_TYPE_32 2
-#define SDS_TYPE_64 3
-#define SDS_TYPE_MASK 3
-#define SDS_TYPE_BITS 2
+#define SDS_TYPE_5  0
+#define SDS_TYPE_8  1
+#define SDS_TYPE_16 2
+#define SDS_TYPE_32 3
+#define SDS_TYPE_64 4
+#define SDS_TYPE_MASK 7
+#define SDS_TYPE_BITS 3
 #define SDS_HDR_VAR(T,s) struct sdshdr##T *sh = (void*)((s)-(sizeof(struct sdshdr##T)));
 #define SDS_HDR(T,s) ((struct sdshdr##T *)((s)-(sizeof(struct sdshdr##T))))
+#define SDS_TYPE_5_LEN(f) ((f)>>SDS_TYPE_BITS)
 
 static inline size_t sdslen(const sds s) {
-    char flags = s[-1];
+    unsigned char flags = s[-1];
     switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5:
+            return SDS_TYPE_5_LEN(flags);
         case SDS_TYPE_8:
             return SDS_HDR(8,s)->len;
         case SDS_TYPE_16:
@@ -89,8 +99,11 @@ static inline size_t sdslen(const sds s) {
 }
 
 static inline size_t sdsavail(const sds s) {
-    char flags = s[-1];
+    unsigned char flags = s[-1];
     switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5: {
+            return 0;
+        }
         case SDS_TYPE_8: {
             SDS_HDR_VAR(8,s);
             return sh->alloc - sh->len;
@@ -112,8 +125,14 @@ static inline size_t sdsavail(const sds s) {
 }
 
 static inline void sdssetlen(sds s, size_t newlen) {
-    char flags = s[-1];
+    unsigned char flags = s[-1];
     switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5:
+            {
+                unsigned char *fp = ((unsigned char*)s)-1;
+                *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
+            }
+            break;
         case SDS_TYPE_8:
             SDS_HDR(8,s)->len = newlen;
             break;
@@ -130,8 +149,15 @@ static inline void sdssetlen(sds s, size_t newlen) {
 }
 
 static inline void sdsinclen(sds s, size_t inc) {
-    char flags = s[-1];
+    unsigned char flags = s[-1];
     switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5:
+            {
+                unsigned char *fp = ((unsigned char*)s)-1;
+                unsigned char newlen = SDS_TYPE_5_LEN(flags)+inc;
+                *fp = SDS_TYPE_5 | (newlen << SDS_TYPE_BITS);
+            }
+            break;
         case SDS_TYPE_8:
             SDS_HDR(8,s)->len += inc;
             break;
@@ -149,8 +175,10 @@ static inline void sdsinclen(sds s, size_t inc) {
 
 /* sdsalloc() = sdsavail() + sdslen() */
 static inline size_t sdsalloc(const sds s) {
-    char flags = s[-1];
+    unsigned char flags = s[-1];
     switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5:
+            return SDS_TYPE_5_LEN(flags);
         case SDS_TYPE_8:
             return SDS_HDR(8,s)->alloc;
         case SDS_TYPE_16:
@@ -164,8 +192,11 @@ static inline size_t sdsalloc(const sds s) {
 }
 
 static inline void sdssetalloc(sds s, size_t newlen) {
-    char flags = s[-1];
+    unsigned char flags = s[-1];
     switch(flags&SDS_TYPE_MASK) {
+        case SDS_TYPE_5:
+            /* Nothing to do, this type has no total allocation info. */
+            break;
         case SDS_TYPE_8:
             SDS_HDR(8,s)->alloc = newlen;
             break;
@@ -193,11 +224,6 @@ sds sdscatsds(sds s, const sds t);
 sds sdscpylen(sds s, const char *t, size_t len);
 sds sdscpy(sds s, const char *t);
 
-/* we can add a reference count on top of any 
- * existing sds. (max up to 63 references) */
-void sdsIncRefcount(sds s);
-void sdsDecRefcount(sds s);
-
 sds sdscatvprintf(sds s, const char *fmt, va_list ap);
 #ifdef __GNUC__
 sds sdscatprintf(sds s, const char *fmt, ...)