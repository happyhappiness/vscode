@@ -57,6 +57,7 @@
 #include <sys/time.h>
 #include <sys/resource.h>
 #include <limits.h>
+#include <math.h>
 
 #include "redis.h"
 #include "ae.h"     /* Event driven programming library */
@@ -338,6 +339,12 @@ struct sharedObjectsStruct {
     *select5, *select6, *select7, *select8, *select9;
 } shared;
 
+/* Global vars that are actally used as constants. The following double
+ * values are used for double on-disk serialization, and are initialized
+ * at runtime to avoid strange compiler optimizations. */
+
+static double R_Zero, R_PosInf, R_NegInf, R_Nan;
+
 /*================================ Prototypes =============================== */
 
 static void freeStringObject(robj *o);
@@ -1021,6 +1028,12 @@ static void initServerConfig() {
     server.masterport = 6379;
     server.master = NULL;
     server.replstate = REDIS_REPL_NONE;
+
+    /* Double constants initialization */
+    R_Zero = 0.0;
+    R_PosInf = 1.0/R_Zero;
+    R_NegInf = -1.0/R_Zero;
+    R_Nan = R_Zero/R_Zero;
 }
 
 static void initServer() {
@@ -2238,6 +2251,33 @@ static int rdbSaveStringObject(FILE *fp, robj *obj) {
     }
 }
 
+/* Save a double value. Doubles are saved as strings prefixed by an unsigned
+ * 8 bit integer specifing the length of the representation.
+ * This 8 bit integer has special values in order to specify the following
+ * conditions:
+ * 253: not a number
+ * 254: + inf
+ * 255: - inf
+ */
+static int rdbSaveDoubleValue(FILE *fp, double val) {
+    unsigned char buf[128];
+    int len;
+
+    if (isnan(val)) {
+        buf[0] = 253;
+        len = 1;
+    } else if (!isfinite(val)) {
+        len = 1;
+        buf[0] = (val < 0) ? 255 : 254;
+    } else {
+        snprintf((char*)buf+1,sizeof(buf)-1,"%.16g",val);
+        buf[0] = strlen((char*)buf);
+        len = buf[0]+1;
+    }
+    if (fwrite(buf,len,1,fp) == 0) return -1;
+    return 0;
+}
+
 /* Save the DB on disk. Return REDIS_ERR on error, REDIS_OK on success */
 static int rdbSave(char *filename) {
     dictIterator *di = NULL;
@@ -2500,6 +2540,23 @@ static robj *rdbLoadStringObject(FILE*fp, int rdbver) {
     return tryObjectSharing(createObject(REDIS_STRING,val));
 }
 
+/* For information about double serialization check rdbSaveDoubleValue() */
+static int rdbLoadDoubleValue(FILE *fp, double *val) {
+    char buf[128];
+    unsigned char len;
+
+    if (fread(&len,1,1,fp) == 0) return -1;
+    switch(len) {
+    case 255: *val = R_NegInf; return 0;
+    case 254: *val = R_PosInf; return 0;
+    case 253: *val = R_Nan; return 0;
+    default:
+        if (fread(buf,len,1,fp) == 0) return -1;
+        sscanf(buf, "%lg", val);
+        return 0;
+    }
+}
+
 static int rdbLoad(char *filename) {
     FILE *fp;
     robj *keyobj = NULL;