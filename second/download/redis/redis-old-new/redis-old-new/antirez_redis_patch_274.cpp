@@ -398,20 +398,18 @@ int getBitOffsetFromArgument(client *c, robj *o, size_t *offset, int hash, int b
     char *err = "bit offset is not an integer or out of range";
     char *p = o->ptr;
     size_t plen = sdslen(p);
+    int usehash = 0;
 
     /* Handle #<offset> form. */
-    if (hash && bits > 0) {
-        p++;
-        plen--;
-    }
+    if (p[0] == '#' && hash && bits > 0) usehash = 1;
 
-    if (string2ll(p,plen,&loffset) == 0) {
+    if (string2ll(p+usehash,plen-usehash,&loffset) == 0) {
         addReplyError(c,err);
         return C_ERR;
     }
 
     /* Adjust the offset by 'bits' for #<offset> form. */
-    if (hash && bits > 0) loffset *= bits;
+    if (usehash) loffset *= bits;
 
     /* Limit offset to 512MB in bytes */
     if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))