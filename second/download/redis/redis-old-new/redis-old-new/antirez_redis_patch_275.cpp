@@ -388,13 +388,30 @@ void printBits(unsigned char *p, unsigned long count) {
 
 /* This helper function used by GETBIT / SETBIT parses the bit offset argument
  * making sure an error is returned if it is negative or if it overflows
- * Redis 512 MB limit for the string value. */
-int getBitOffsetFromArgument(client *c, robj *o, size_t *offset) {
+ * Redis 512 MB limit for the string value.
+ *
+ * If the 'hash' argument is true, and 'bits is positive, then the command
+ * will also parse bit offsets prefixed by "#". In such a case the offset
+ * is multiplied by 'bits'. This is useful for the BITFIELD command. */
+int getBitOffsetFromArgument(client *c, robj *o, size_t *offset, int hash, int bits) {
     long long loffset;
     char *err = "bit offset is not an integer or out of range";
+    char *p = o->ptr;
+    size_t plen = sdslen(p);
+
+    /* Handle #<offset> form. */
+    if (hash && bits > 0) {
+        p++;
+        plen--;
+    }
 
-    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != C_OK)
+    if (string2ll(p,plen,&loffset) == 0) {
+        addReplyError(c,err);
         return C_ERR;
+    }
+
+    /* Adjust the offset by 'bits' for #<offset> form. */
+    if (hash && bits > 0) loffset *= bits;
 
     /* Limit offset to 512MB in bytes */
     if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
@@ -469,7 +486,7 @@ void setbitCommand(client *c) {
     int byteval, bitval;
     long on;
 
-    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != C_OK)
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset,0,0) != C_OK)
         return;
 
     if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != C_OK)
@@ -507,7 +524,7 @@ void getbitCommand(client *c) {
     size_t byte, bit;
     size_t bitval = 0;
 
-    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != C_OK)
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset,0,0) != C_OK)
         return;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
@@ -908,7 +925,7 @@ void bitfieldCommand(client *c) {
             return;
         }
 
-        if (getBitOffsetFromArgument(c,c->argv[j+2],&bitoffset) != C_OK) {
+        if (getBitOffsetFromArgument(c,c->argv[j+2],&bitoffset,1,bits) != C_OK){
             zfree(ops);
             return;
         }