@@ -116,6 +116,25 @@ static sds sdsMakeRoomFor(sds s, size_t addlen) {
     return newsh->buf;
 }
 
+/* Grow the sds to have the specified length. Bytes that were not part of
+ * the original length of the sds will be set to NULL. */
+sds sdsgrowsafe(sds s, size_t len) {
+    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
+    size_t totlen, curlen = sh->len;
+
+    if (len <= curlen) return s;
+    s = sdsMakeRoomFor(s,len-curlen);
+    if (s == NULL) return NULL;
+
+    /* Make sure added region doesn't contain garbage */
+    sh = (void*)(s-(sizeof(struct sdshdr)));
+    memset(s+curlen,0,(len-curlen+1)); /* also set trailing NULL byte */
+    totlen = sh->len+sh->free;
+    sh->len = len;
+    sh->free = totlen-sh->len;
+    return s;
+}
+
 sds sdscatlen(sds s, void *t, size_t len) {
     struct sdshdr *sh;
     size_t curlen = sdslen(s);
@@ -155,32 +174,6 @@ sds sdscpy(sds s, char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
-sds sdssetbit(sds s, size_t bit, int on) {
-    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
-    int byte = bit >> 3;
-    int reqlen = byte+1;
-
-    if (reqlen > sh->len) {
-        size_t totlen;
-
-        s = sdsMakeRoomFor(s,reqlen-sh->len);
-        if (s == NULL) return NULL;
-        sh = (void*)(s-(sizeof(struct sdshdr)));
-
-        /* Make sure added region doesn't contain garbage */
-        totlen = sh->len+sh->free;
-        memset(s+sh->len,0,sh->free+1);
-        sh->len = reqlen;
-        sh->free = totlen-sh->len;
-    }
-
-    bit = 7 - (bit & 0x7);
-    on &= 0x1;
-    s[byte] |= on << bit;
-    s[byte] &= ~((!on) << bit);
-    return s;
-}
-
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char *buf, *t;