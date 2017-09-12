@@ -155,6 +155,32 @@ sds sdscpy(sds s, char *t) {
     return sdscpylen(s, t, strlen(t));
 }
 
+sds sdssetbit(sds s, size_t bit, int on) {
+    struct sdshdr *sh = (void*)(s-(sizeof(struct sdshdr)));
+    int byte = bit >> 3;
+    int reqlen = byte+1;
+
+    if (reqlen > sh->len) {
+        size_t totlen;
+
+        s = sdsMakeRoomFor(s,reqlen-sh->len);
+        if (s == NULL) return NULL;
+        sh = (void*)(s-(sizeof(struct sdshdr)));
+
+        /* Make sure added region doesn't contain garbage */
+        totlen = sh->len+sh->free;
+        memset(s+sh->len,0,sh->free+1);
+        sh->len = reqlen;
+        sh->free = totlen-sh->len;
+    }
+
+    bit = 7 - (bit & 0x7);
+    on &= 0x1;
+    s[byte] |= on << bit;
+    s[byte] &= ~((!on) << bit);
+    return s;
+}
+
 sds sdscatvprintf(sds s, const char *fmt, va_list ap) {
     va_list cpy;
     char *buf, *t;