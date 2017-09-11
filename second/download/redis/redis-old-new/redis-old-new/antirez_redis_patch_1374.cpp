@@ -56,7 +56,16 @@ robj *createStringObjectFromLongDouble(long double value) {
      * that is "non surprising" for the user (that is, most small decimal
      * numbers will be represented in a way that when converted back into
      * a string are exactly the same as what the user typed.) */
-    len = snprintf(buf,sizeof(buf),"%.17Lg", value);
+    len = snprintf(buf,sizeof(buf),"%.17Lf", value);
+    /* Now remove trailing zeroes after the '.' */
+    if (strchr(buf,'.') != NULL) {
+        char *p = buf+len-1;
+        while(*p == '0') {
+            p--;
+            len--;
+        }
+        if (*p == '.') len--;
+    }
     return createStringObject(buf,len);
 }
 
@@ -95,12 +104,9 @@ robj *createIntsetObject(void) {
 }
 
 robj *createHashObject(void) {
-    /* All the Hashes start as zipmaps. Will be automatically converted
-     * into hash tables if there are enough elements or big elements
-     * inside. */
-    unsigned char *zm = zipmapNew();
-    robj *o = createObject(REDIS_HASH,zm);
-    o->encoding = REDIS_ENCODING_ZIPMAP;
+    unsigned char *zl = ziplistNew();
+    robj *o = createObject(REDIS_HASH, zl);
+    o->encoding = REDIS_ENCODING_ZIPLIST;
     return o;
 }
 
@@ -176,7 +182,7 @@ void freeHashObject(robj *o) {
     case REDIS_ENCODING_HT:
         dictRelease((dict*) o->ptr);
         break;
-    case REDIS_ENCODING_ZIPMAP:
+    case REDIS_ENCODING_ZIPLIST:
         zfree(o->ptr);
         break;
     default:
@@ -492,7 +498,6 @@ char *strEncoding(int encoding) {
     case REDIS_ENCODING_RAW: return "raw";
     case REDIS_ENCODING_INT: return "int";
     case REDIS_ENCODING_HT: return "hashtable";
-    case REDIS_ENCODING_ZIPMAP: return "zipmap";
     case REDIS_ENCODING_LINKEDLIST: return "linkedlist";
     case REDIS_ENCODING_ZIPLIST: return "ziplist";
     case REDIS_ENCODING_INTSET: return "intset";