@@ -5197,15 +5197,29 @@ static void zrangebyscoreCommand(redisClient *c) {
     double min = strtod(c->argv[2]->ptr,NULL);
     double max = strtod(c->argv[3]->ptr,NULL);
     int offset = 0, limit = -1;
+    int withscores = 0;
+    int badsyntax = 0;
+
+    if (c->argc == 5 || c->argc == 8) {
+        if (strcasecmp(c->argv[c->argc-1]->ptr,"withscores") == 0) withscores = 1;
+        else badsyntax = 1;
+    }
+
+    if (c->argc != (4 + withscores) && c->argc != (7 + withscores)) {
+        badsyntax = 1;
+    }
 
-    if (c->argc != 4 && c->argc != 7) {
+
+    if (badsyntax) {
         addReplySds(c,
             sdsnew("-ERR wrong number of arguments for ZRANGEBYSCORE\r\n"));
         return;
-    } else if (c->argc == 7 && strcasecmp(c->argv[4]->ptr,"limit")) {
+    }
+
+    if (c->argc == (7 + withscores) && strcasecmp(c->argv[4]->ptr,"limit")) {
         addReply(c,shared.syntaxerr);
         return;
-    } else if (c->argc == 7) {
+    } else if (c->argc == (7 + withscores)) {
         offset = atoi(c->argv[5]->ptr);
         limit = atoi(c->argv[6]->ptr);
         if (offset < 0) offset = 0;
@@ -5251,11 +5265,14 @@ static void zrangebyscoreCommand(redisClient *c) {
                 addReplyBulkLen(c,ele);
                 addReply(c,ele);
                 addReply(c,shared.crlf);
+                if (withscores)
+                    addReplyDouble(c,ln->score);
                 ln = ln->forward[0];
                 rangelen++;
                 if (limit > 0) limit--;
             }
-            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",rangelen);
+            lenobj->ptr = sdscatprintf(sdsempty(),"*%d\r\n",
+		 withscores ? (rangelen*2) : rangelen);
         }
     }
 }