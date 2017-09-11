@@ -318,7 +318,8 @@ int checkSignedBitfieldOverflow(int64_t value, int64_t incr, uint64_t bits, int
     int64_t maxincr = max-value;
     int64_t minincr = min-value;
 
-    if (value > max || (value >= 0 && incr > 0 && incr > maxincr)) {
+    if (value > max || (bits == 64 && value >= 0 && incr > 0 && incr > maxincr)
+            || (bits < 64 && incr > 0 && incr > maxincr)) {
         if (limit) {
             if (owtype == BFOVERFLOW_WRAP) {
                 goto handle_wrap;
@@ -327,7 +328,8 @@ int checkSignedBitfieldOverflow(int64_t value, int64_t incr, uint64_t bits, int
             }
         }
         return 1;
-    } else if (value < min || (value < 0 && incr < 0 && incr < minincr)) {
+    } else if (value < min || (bits == 64 && value < 0 && incr < 0 && incr < minincr)
+            || (bits < 64 && incr < 0 && incr < minincr)) {
         if (limit) {
             if (owtype == BFOVERFLOW_WRAP) {
                 goto handle_wrap;
@@ -445,8 +447,8 @@ int getBitfieldTypeFromArgument(client *c, robj *o, int *sign, int *bits) {
 
     if ((string2ll(p+1,strlen(p+1),&llbits)) == 0 ||
         llbits < 1 ||
-        (*sign == 1 && llbits > 63) ||
-        (*sign == 0 && llbits > 64))
+        (*sign == 1 && llbits > 64) ||
+        (*sign == 0 && llbits > 63))
     {
         addReplyError(c,err);
         return C_ERR;
@@ -963,7 +965,8 @@ void bitfieldCommand(client *c) {
              * for simplicity. SET return value is the previous value so
              * we need fetch & store as well. */
 
-            if ((o = lookupStringForBitCommand(c,bitoffset)) == NULL) return;
+            if ((o = lookupStringForBitCommand(c,thisop->offset + thisop->bits))
+                    == NULL) return;
 
             /* We need two different but very similar code paths for signed
              * and unsigned operations, since the set of functions to get/set