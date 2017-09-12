@@ -3623,9 +3623,8 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     int prefixlen, sublen, postfixlen;
     /* Expoit the internal sds representation to create a sds string allocated on the stack in order to make this function faster */
     struct {
-        int len;
-        unsigned short free;
-        unsigned short _len; /* not used here */
+        long len;
+        long free;
         char buf[REDIS_SORTKEY_MAX+1];
     } keyname;
 
@@ -3649,7 +3648,6 @@ static robj *lookupKeyByPattern(redisDb *db, robj *pattern, robj *subst) {
     memcpy(keyname.buf+prefixlen+sublen,p+1,postfixlen);
     keyname.buf[prefixlen+sublen+postfixlen] = '\0';
     keyname.len = prefixlen+sublen+postfixlen;
-    keyname._len = USHRT_MAX;
 
     keyobj.refcount = 1;
     keyobj.type = REDIS_STRING;
@@ -3847,9 +3845,9 @@ static void sortCommand(redisClient *c) {
                     if (byval->encoding == REDIS_ENCODING_RAW) {
                         vector[j].u.score = strtod(byval->ptr,NULL);
                     } else {
-                        if (byval->encoding == REDIS_ENCODING_INT)
+                        if (byval->encoding == REDIS_ENCODING_INT) {
                             vector[j].u.score = (long)byval->ptr;
-                        else
+                        } else
                             assert(1 != 1);
                     }
                 }
@@ -3936,6 +3934,7 @@ static void infoCommand(redisClient *c) {
     
     info = sdscatprintf(sdsempty(),
         "redis_version:%s\r\n"
+        "arch_bits:%s\r\n"
         "uptime_in_seconds:%d\r\n"
         "uptime_in_days:%d\r\n"
         "connected_clients:%d\r\n"
@@ -3948,6 +3947,7 @@ static void infoCommand(redisClient *c) {
         "total_commands_processed:%lld\r\n"
         "role:%s\r\n"
         ,REDIS_VERSION,
+        (sizeof(long) == 8) ? "64" : "32",
         uptime,
         uptime/(3600*24),
         listLength(server.clients)-listLength(server.slaves),