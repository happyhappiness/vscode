@@ -41,18 +41,18 @@ static int getBitOffsetFromArgument(client *c, robj *o, size_t *offset) {
     long long loffset;
     char *err = "bit offset is not an integer or out of range";
 
-    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != REDIS_OK)
-        return REDIS_ERR;
+    if (getLongLongFromObjectOrReply(c,o,&loffset,err) != C_OK)
+        return C_ERR;
 
     /* Limit offset to 512MB in bytes */
     if ((loffset < 0) || ((unsigned long long)loffset >> 3) >= (512*1024*1024))
     {
         addReplyError(c,err);
-        return REDIS_ERR;
+        return C_ERR;
     }
 
     *offset = (size_t)loffset;
-    return REDIS_OK;
+    return C_OK;
 }
 
 /* Count number of bits set in the binary array pointed by 's' and long
@@ -217,10 +217,10 @@ void setbitCommand(client *c) {
     int byteval, bitval;
     long on;
 
-    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != C_OK)
         return;
 
-    if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[3],&on,err) != C_OK)
         return;
 
     /* Bits can only be set or cleared... */
@@ -263,7 +263,7 @@ void getbitCommand(client *c) {
     size_t byte, bit;
     size_t bitval = 0;
 
-    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != REDIS_OK)
+    if (getBitOffsetFromArgument(c,c->argv[2],&bitoffset) != C_OK)
         return;
 
     if ((o = lookupKeyReadOrReply(c,c->argv[1],shared.czero)) == NULL ||
@@ -479,9 +479,9 @@ void bitcountCommand(client *c) {
 
     /* Parse start/end range if any. */
     if (c->argc == 4) {
-        if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != REDIS_OK)
+        if (getLongFromObjectOrReply(c,c->argv[2],&start,NULL) != C_OK)
             return;
-        if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != REDIS_OK)
+        if (getLongFromObjectOrReply(c,c->argv[3],&end,NULL) != C_OK)
             return;
         /* Convert negative indexes */
         if (start < 0) start = strlen+start;
@@ -520,7 +520,7 @@ void bitposCommand(client *c) {
 
     /* Parse the bit argument to understand what we are looking for, set
      * or clear bits. */
-    if (getLongFromObjectOrReply(c,c->argv[2],&bit,NULL) != REDIS_OK)
+    if (getLongFromObjectOrReply(c,c->argv[2],&bit,NULL) != C_OK)
         return;
     if (bit != 0 && bit != 1) {
         addReplyError(c, "The bit argument must be 1 or 0.");
@@ -548,10 +548,10 @@ void bitposCommand(client *c) {
 
     /* Parse start/end range if any. */
     if (c->argc == 4 || c->argc == 5) {
-        if (getLongFromObjectOrReply(c,c->argv[3],&start,NULL) != REDIS_OK)
+        if (getLongFromObjectOrReply(c,c->argv[3],&start,NULL) != C_OK)
             return;
         if (c->argc == 5) {
-            if (getLongFromObjectOrReply(c,c->argv[4],&end,NULL) != REDIS_OK)
+            if (getLongFromObjectOrReply(c,c->argv[4],&end,NULL) != C_OK)
                 return;
             end_given = 1;
         } else {