@@ -1150,7 +1150,7 @@ static void getRDB(void) {
 
     while(payload) {
         ssize_t nread, nwritten;
-        
+
         nread = read(s,buf,(payload > sizeof(buf)) ? sizeof(buf) : payload);
         if (nread <= 0) {
             fprintf(stderr,"I/O Error reading RDB payload from socket\n");
@@ -1233,7 +1233,7 @@ static void pipeMode(void) {
                         errors++;
                     } else if (eof && reply->type == REDIS_REPLY_STRING &&
                                       reply->len == 20) {
-                        /* Check if this is the reply to our final ECHO 
+                        /* Check if this is the reply to our final ECHO
                          * command. If so everything was received
                          * from the server. */
                         if (memcmp(reply->str,magic,20) == 0) {
@@ -1254,7 +1254,7 @@ static void pipeMode(void) {
                 /* Transfer current buffer to server. */
                 if (obuf_len != 0) {
                     ssize_t nwritten = write(fd,obuf+obuf_pos,obuf_len);
-                    
+
                     if (nwritten == -1) {
                         if (errno != EAGAIN && errno != EINTR) {
                             fprintf(stderr, "Error writing to the server: %s\n",
@@ -1357,7 +1357,7 @@ static redisReply *sendScan(unsigned long long *it) {
     /* Validate our types are correct */
     assert(reply->element[0]->type == REDIS_REPLY_STRING);
     assert(reply->element[1]->type == REDIS_REPLY_ARRAY);
-    
+
     /* Update iterator */
     *it = atoi(reply->element[0]->str);
 
@@ -1369,7 +1369,7 @@ static int getDbSize(void) {
     int size;
 
     reply = redisCommand(context, "DBSIZE");
-    
+
     if(reply == NULL || reply->type != REDIS_REPLY_INTEGER) {
         fprintf(stderr, "Couldn't determine DBSIZE!\n");
         exit(1);
@@ -1422,13 +1422,13 @@ static void getKeyTypes(redisReply *keys, int *types) {
             exit(1);
         }
 
-        types[i] = toIntType(keys->element[i]->str, reply->str); 
+        types[i] = toIntType(keys->element[i]->str, reply->str);
         freeReplyObject(reply);
     }
 }
 
-static void getKeySizes(redisReply *keys, int *types, 
-                        unsigned long long *sizes) 
+static void getKeySizes(redisReply *keys, int *types,
+                        unsigned long long *sizes)
 {
     redisReply *reply;
     char *sizecmds[] = {"STRLEN","LLEN","SCARD","HLEN","ZCARD"};
@@ -1437,10 +1437,10 @@ static void getKeySizes(redisReply *keys, int *types,
     /* Pipeline size commands */
     for(i=0;i<keys->elements;i++) {
         /* Skip keys that were deleted */
-        if(types[i]==TYPE_NONE) 
+        if(types[i]==TYPE_NONE)
             continue;
 
-        redisAppendCommand(context, "%s %s", sizecmds[types[i]], 
+        redisAppendCommand(context, "%s %s", sizecmds[types[i]],
             keys->element[i]->str);
     }
 
@@ -1460,14 +1460,14 @@ static void getKeySizes(redisReply *keys, int *types,
         } else if(reply->type != REDIS_REPLY_INTEGER) {
             /* Theoretically the key could have been removed and
              * added as a different type between TYPE and SIZE */
-            fprintf(stderr, 
+            fprintf(stderr,
                 "Warning:  %s on '%s' failed (may have changed type)\n",
                  sizecmds[types[i]], keys->element[i]->str);
             sizes[i] = 0;
         } else {
             sizes[i] = reply->integer;
         }
-            
+
         freeReplyObject(reply);
     }
 }
@@ -1524,12 +1524,12 @@ static void findBigKeys(void) {
         /* Retreive types and then sizes */
         getKeyTypes(keys, types);
         getKeySizes(keys, types, sizes);
-        
+
         /* Now update our stats */
         for(i=0;i<keys->elements;i++) {
             if((type = types[i]) == TYPE_NONE)
                 continue;
-            
+
             totalsize[type] += sizes[i];
             counts[type]++;
             totlen += keys->element[i]->len;
@@ -1549,7 +1549,7 @@ static void findBigKeys(void) {
                 }
 
                 /* Keep track of the biggest size for this type */
-                biggest[type] = sizes[i];                
+                biggest[type] = sizes[i];
             }
 
             /* Update overall progress */
@@ -1562,7 +1562,7 @@ static void findBigKeys(void) {
         if(sampled && (sampled %100) == 0 && config.interval) {
             usleep(config.interval);
         }
-        
+
         freeReplyObject(reply);
     } while(it != 0);
 