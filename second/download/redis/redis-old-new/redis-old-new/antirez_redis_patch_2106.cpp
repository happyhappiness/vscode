@@ -2897,7 +2897,19 @@ static robj *createStringObjectFromLongLong(long long value) {
             o->encoding = REDIS_ENCODING_INT;
             o->ptr = (void*)((long)value);
         } else {
-            o->ptr = sdscatprintf(sdsempty(),"%lld",value);
+            char buf[32], *p;
+            char *c = "0123456789";
+            unsigned long v;
+
+            v = (value < 0) ? -value : value;
+            p = buf+31; /* point to the last character */
+            while(v) {
+                *p-- = c[v%10];
+                v /= 10;
+            }
+            if (value < 0) *p-- = '-';
+            p++;
+            o = createObject(REDIS_STRING,sdsnewlen(p,32-(p-buf+1)));
         }
     }
     return o;
@@ -3794,7 +3806,7 @@ static robj *rdbLoadIntegerObject(FILE *fp, int enctype) {
         val = 0; /* anti-warning */
         redisPanic("Unknown RDB integer encoding type");
     }
-    return createObject(REDIS_STRING,sdscatprintf(sdsempty(),"%lld",val));
+    return createStringObjectFromLongLong(val);
 }
 
 static robj *rdbLoadLzfStringObject(FILE*fp) {